@echo off

robocopy /NJS /NJH /S assets vs2013/TestProject/assets
robocopy /NJS /NJH /S assets android/assets
exit