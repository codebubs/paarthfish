@echo off
g++ *.cpp -o app
app.exe
del "./app.exe"