@ECHO OFF
FOR %%F IN (*.mesh) DO (
Flour.exe meshes type: Triangle, in: %%F, out: %%F.nxs
ECHO .
)
