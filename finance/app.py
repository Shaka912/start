import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime,date
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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    symbol= db.execute("SELECT symbol FROM transactions WHERE trx_id=?", session["user_id"])
    update= lookup(symbol)
    name= update["name"]
    shares= db.execute("SELECT shares FROM transactions WHERE trx_id=?", session["user_id"])
    
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        sym= request.form.get("symbol")
        shares= int(request.form.get("shares"))
        update= lookup(sym)
        if not sym or not shares:
            return apology("Missing field Symbol / or shares")
        elif update == None:
            return apology("Please enter Valid stock symbol")
        elif shares == None:
            return apology("Please enter valid positive number")
        trx = update["price"] * shares
        # update user balance
        capital = db.execute("SELECT cash FROM users WHERE id= ?", session["user_id"])
        if trx <= capital[0]["cash"]:
            new_capital=  capital[0]["cash"] - trx
            today = date.today()
            d = today.strftime("%d/%m/%Y")
            now = datetime.now()
            current_time = now.strftime("%H:%M:%S")
            db.execute("UPDATE users SET cash= ? WHERE id =?", new_capital, session["user_id"])
            db.execute("INSERT INTO transactions (trx_id,symbol, price, shares, date, time) VALUES(?,?, ?,?,?,?)" ,session["user_id"]
            ,sym,update["price"],shares, d, current_time)
            flash("Stocks Purchased")
            return redirect("/")
        else:
            return apology("Insufficient funds")
    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        sym = request.form.get("sym")

        update=lookup(sym)
        if update is None:
            return apology("Please enter valid stock name")
        return render_template("quoted.html", update=update)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username= request.form.get("username")
        password= request.form.get("password")
        passwordag= request.form.get("confirmation")
        userlist = db.execute("SELECT * FROM users WHERE username = ?", username)

        if not username or not password:
            return apology("username or password is missing")
        elif len(userlist) > 0:
            return apology("Username already exist")
        if passwordag != password:
            return apology("password do not match")
        hash = generate_password_hash("password", method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES(?,?)", username,hash )
        userlist1 = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = userlist1[0]["id"]
        flash("Registered")
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
