import sqlite3


conn = sqlite3.connect("data.db")
cursor = conn.cursor()

res = cursor.execute("SELECT * FROM Device")
res = res.fetchall()[0]
print(type(res))
conn.close()