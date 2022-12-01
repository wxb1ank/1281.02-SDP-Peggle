@echo off

set git=%~1
set repo_dir=%~2
set repo_url=%~3

ping -n 1 -w 1000 %repo_url%
if not errorlevel 1 (
    if exist "%repo_dir%" (
        %git% -C "%repo_dir%" stash
        %git% -C "%repo_dir%" pull
    ) else (
        %git% clone %repo_url%
    )
)
