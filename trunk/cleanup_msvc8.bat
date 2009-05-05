@echo >>>>>>>>>>> Cleaning up... <<<<<<<<<<<
@del *.ncb /S
@del *.suo /AH /S
@del *.user /S
@del *.lib /S
@del *.ilk /S
@del *.exp /S
@del *.pdb /S
@del *.user /S
@del *.pch /S
@del BuildLog.htm /S
@rmdir Obj\Release\ /S /Q
@rmdir Obj\Debug\ /S /Q
@echo >>>>>>>>>>>     Done!      <<<<<<<<<<<
