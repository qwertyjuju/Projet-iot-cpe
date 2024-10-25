import sqlite3

# Connect to the database
conn = sqlite3.connect('data.db')
cursor = conn.cursor()