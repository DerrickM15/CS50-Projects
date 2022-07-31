import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    name = user[0]['username']
    user_cash = user[0]['cash']
    stocks = db.execute(
        "SELECT symbol, name, price, SUM(shares), SUM(total_cost) FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    sum_of_all_stocks = db.execute("SELECT SUM(total_cost) FROM transactions WHERE user_id = ?", session["user_id"])
    stock_value = sum_of_all_stocks[0]['SUM(total_cost)']
    stocks_symbols = []
    current_values = []
    if request.method == "POST":
        add_cash = float(request.form.get("amount"))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (user_cash + add_cash), session["user_id"])
        return redirect("/")
    else:
        if not stocks:
            return render_template("buy.html")
        else:
            for stock in stocks:
                stocks_symbols.append(stock["symbol"])
                current_values.append(lookup(stock["symbol"])["price"])
            value_dict = dict(zip(stocks_symbols, current_values))
            return render_template("index.html", user=user, name=name, stocks=stocks, user_cash=user_cash, stock_value=stock_value, value_dict=value_dict)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # db.execute("CREATE TABLE transactions(user_id INTEGER NOT NULL, symbol TEXT NOT NULL, name TEXT NOT NULL, price NUMERIC NOT NULL, shares INTEGER NOT NULL, date TEXT, total_cost NUMERIC NOT NULL, FOREIGN KEY(user_id) REFERENCES users(id))")
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Please enter stock", 400)
        elif not request.form.get("shares"):
            return apology("Please enter shares", 400)
        elif request.form.get("shares") == 'foo':
            return apology("shares must be a number")
        elif request.form.get("shares") == None:
            return apology("shares must be a number")
        elif stock == None:
            return apology("Stock does not exist", 400)
        symbol = stock["symbol"]
        shares_quantity = float(request.form.get("shares"))
        if shares_quantity < 0:
            return apology("Please enter stock quantity", 400)
        elif shares_quantity.is_integer() == False:
            return apology("Stock Quantity must be whole number", 400)
        elif isinstance(shares_quantity, float) == False:
            return apology("Stock quantity must be a number", 400)
        else:
            stock_price = stock["price"]
            total_cost = stock_price * shares_quantity
            name = stock["name"]
            current_user = session.get("user_id")
            wallet = db.execute("SELECT cash FROM users WHERE id = ?", current_user)
            user_cash = wallet[0]["cash"]
            if total_cost > user_cash:
                return apology("Not enough money for stock", 400)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", (user_cash - total_cost), session["user_id"])
            db.execute("INSERT INTO transactions (user_id, symbol, shares, type, price, date, time, name, total_cost) VALUES(?,?,?, 'buy', ?,(SELECT date()), (SELECT time()),?,?)",
                       session["user_id"], symbol, shares_quantity, stock_price, name, total_cost)
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    name = user[0]['username']
    stocks = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", name=name, stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        if not symbol:
            return apology("Please enter stock", 400)
        elif symbol == None:
            return apology("Please enter stock", 400)
        elif not stock:
            return apology("Stock does not exist", 400)
        elif stock == None:
            return apology("Stock does not exist", 400)
        else:
            return render_template("quoted.html", symbol=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if not username:
            return apology("must provide username", 400)

        elif len(rows) > 0:
            return apology("username already exists", 400)

        elif not password:
            return apology("must provide password", 400)

        elif not confirmation:
            return apology("must confirm password", 400)

        elif confirmation != password:
            return apology("passwords do not match", 400)

        else:
            hash = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    stocks = db.execute("SELECT * FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)
    else:
        current_user = session.get("user_id")
        stock = lookup(request.form.get("symbol"))
        name = stock["name"]
        symbol = stock["symbol"]
        stock_price = stock["price"]
        shares_quantity = float(request.form.get("shares"))
        total = stock_price * (0 - shares_quantity)
        wallet = db.execute("SELECT cash FROM users WHERE id = ?", current_user)
        user_cash = wallet[0]["cash"]
        shares_to_sell = db.execute("SELECT SUM(shares) from transactions WHERE user_id = ? GROUP BY symbol", current_user)
        if not request.form.get("symbol"):
            return apology("Must select stocks to sell", 400)
        elif not request.form.get("shares"):
            return apology("Must select amount of shares to sell", 400)
        elif shares_quantity < 1:
            return apology("shares amount must be positive", 400)
        elif shares_quantity > shares_to_sell[0]["SUM(shares)"]:
            return apology("Not enough shares to sell", 400)
        elif shares_quantity.is_integer() == False:
            return apology("shares amount must be whole number", 400)
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash - total, current_user)
            db.execute("INSERT INTO transactions (user_id, symbol, shares, type, price, date, time, name, total_cost) VALUES(?,?,?, 'sell', ?,(SELECT date()), (SELECT time()),?,?)",
                       session["user_id"], symbol, 0 - shares_quantity, stock_price, name, total)
            return redirect("/")
