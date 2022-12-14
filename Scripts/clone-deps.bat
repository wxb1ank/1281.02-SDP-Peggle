@echo off

set git=%~1
set repo_dir=%~2
set repo_url=%~3

ping -n 1 -w 1000 google.com
if not errorlevel 1 (
    if not exist "%repo_dir%" (
        %git% clone %repo_url% "%repo_dir%"
    )
)
