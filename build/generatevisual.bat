@IF EXIST genie.exe (
  @genie.exe vs2015
)
  @IF NOT EXIST genie.exe (
  @echo ERROR: Cannot find genie.exe file.
  @echo        unzip build\genie.zip in order to obtain it.   
  @pause
)

