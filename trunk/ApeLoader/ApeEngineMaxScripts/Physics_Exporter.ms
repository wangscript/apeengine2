--//////////////////////////////////////////////////////////////
--// Physics Exporter for OgreMax
--// ------- -------- --- -------
--// Work in progress...
--// 
--// More info:
--// Link: http://www.ogre3d.org/phpBB2addons/viewtopic.php?t=8180&postdays=0&postorder=asc&start=0
--//////////////////////////////////////////////////////////////

try ( --Destroy previous dialogs
	destroyDialog sceneparams
)
catch()

--Remove the callback if was previously added (not necesary?)
callbacks.removeScripts id:#MrGAG
--This is to add the Physics rollout menu for each object in the scene
callbacks.addScript #selectionSetChanged "setRolloutControls()" id:#MrGAG

callbacks.addScript #filePostOpenProcess "sceneFileOpened()" id:#MrGAG
callbacks.addScript #filePostSave "sceneFileSaved()" id:#MrGAG
callbacks.addScript #systemPostReset "sceneReset()" id:#MrGAG

--#pluginLoaded
--callbacks.addScript #pluginLoaded "print (callbacks.notificationParam())" id:#MXSHelp

fn existFile fname = (getfiles fname).count != 0

--fn convertObjectsToActors =
--(

--)



fn updateObject =
(
	--if objName == "" Then
	--(
		--Im paranoid
	--	print("Error: Empty parameter")

	--)
	--else
	--(
	
	
		for o in cameras do 
		(
			if o != undefined Then
			(
				--print o.name
				error = "False"
				--print "error aca:" + (o.name as string)
				settings = ogremax.GetObjectSettingsByName(o.name)
				settings.UserData = ""
						
				--custAttributes.add o newAttrib #Unique
				if (custAttributes.count o) == 0 Then
				(
					try (custAttributes.add o newAttrib)
					catch(
						print("Error in custAttributes.add")
						error = "True"
					)					

				)
			
				if (error == "False") Then
				(
					settings.UserData += "\r\n" + "parentRoom:" + (getUserProp o "parentName" as string)
				)
				if o.exportEnabled == false Then
				(
					settings.UserData += "\r\n" + "enabled:false"
				)
			)
		)
	
	
		for o in lights do 
		(
			if o != undefined Then
			(
				--print o.name
				error = "False"
				--print "error aca:" + (o.name as string)
				settings = ogremax.GetObjectSettingsByName(o.name)
				settings.UserData = ""
						
				--custAttributes.add o newAttrib #Unique
				if (custAttributes.count o) == 0 Then
				(
					try (custAttributes.add o newAttrib)
					catch(
						print("Error in custAttributes.add")
						error = "True"
					)					

				)
			
				if (error == "False") Then
				(
					settings.UserData += "\r\n" + "parentRoom:" + (getUserProp o "parentName" as string)
				)
				if o.exportEnabled == false Then
				(
					settings.UserData += "\r\n" + "enabled:false"
				)
			)
		)
		
		for o in geometry do 
		(
			if o != undefined Then
			(

					--print o.name
				
					error = "False"

					--custAttributes.add o newAttrib #Unique
					if (custAttributes.count o) == 0 Then
					(
						try (custAttributes.add o newAttrib)
						catch(
							print("Error in custAttributes.add")
							error = "True"
						)					

					)
			
					if (error) == "False" Then
					(
						i = 0
						
						setUserProp o "numChildrens" "0"
						--o.pivot = o.center
						
						--ResetTransform o
						--ResetScale o
						--ResetPivot o
						--print "Material: " + o.material as string
						
					
						for child in o.children do
						(
							--setUserProp child ("childOf:" + 
							
							i = i + 1
							setUserProp o "numChildrens" (i as string)
							setUserProp o ("childNode" + (i as string)) (child.name)
							
							--ResetTransform child
							--ResetScale child
							--ResetPivot child
							
							--print(child.name as string + " - Hijo de: " + child.parent.name as string)
						)
			
						--if (i) > 0 Then
						--(
						--	ResetTransform o
						--)
						
						--st = (getUserProp o "soundType" as string)
						--print st as string

						--if st == "custom" do
						--(

							
							--o.predefSounds.selected = (sn as string)
						--)
						--if st == "predefined" do
						--(
							
						--)						
			
						settings = ogremax.GetObjectSettingsByName(o.name)
						settings.UserData = ""
						
						--If it doesn't has a mesh name, create one
						--if settings.MeshName == "" then
						--(
							settings.UserData = "entityName:" + o.name
							settings.UserData += "\r\n" + "meshName:" + o.name + ".mesh"
						--)
						--else
						--(
						--	settings.UserData = "entityName:" + o.name
						--	settings.UserData += "\r\n" + "meshName:" + settings.MeshName
						--)
					
					
					
						
						
					
						--Add new line
						--settings.UserData += "\r\n"
							soundType = (getUserProp o "soundType" as string)
							settings.UserData += "\r\n" + "soundType:" + soundType as string
							soundSize = (getUserProp o "soundSize" as string)
							settings.UserData += "\r\n" + "soundSize:" + soundSize as string
							soundName = (getUserProp o "soundName" as string)
							settings.UserData += "\r\n" + "soundName:" + soundName as string


						
						if (o.baseObject as string == "Editable Mesh") or 
							(o.baseObject as string == "Editable Poly") Then 
						(				
							o.type = 4
							settings.UserData += "\r\n" + "shapeType:EditableMesh"
						)
						else
						(
							if classof o.baseObject == Box Then
							(
								o.type = 1
								settings.UserData += "\r\n" + "shapeType:Box"
								settings.UserData += "\r\n" + "size:" + o.width as string + " " + o.height as string + " " + o.length as string + " "
							)
							if classof o.baseObject == Sphere Then
							(
								o.type = 2
								settings.UserData += "\r\n" + "shapeType:Sphere"
								settings.UserData += "\r\n" + "size:" + o.radius as string
							)
							if classof o.baseObject == Capsule Then
							(
								o.type = 3
								settings.UserData += "\r\n" + "shapeType:Capsule"
								settings.UserData += "\r\n" + "size:" + o.radius as string + " " + o.height as string
							)
							if classof o.baseObject == Portal Then
							(
								--o.type = 4
								settings.UserData += "\r\n" + "shapeType:Portal"
								settings.UserData += "\r\n" + "size:" + o.length as string + " " + o.width as string
								settings.UserData += "\r\n" + "parentRoom1:" + (getUserProp o "parentRoom1" as string)
								settings.UserData += "\r\n" + "parentRoom2:" + (getUserProp o "parentRoom2" as string)
								
							)
							if classof o.baseObject == ParentRoom Then
							(
								o.type = 1
								settings.UserData += "\r\n" + "shapeType:ParentRoom"
								offset = 5
								settings.UserData += "\r\n" + "size:" + (o.width + offset) as string + " " + (o.height + offset) as string + " " + (o.length + offset) as string + " "
								settings.UserData += "\r\n" + "cameraName:" + (getUserProp o "cameraName" as string)

								--settings.UserData += "\r\n" + "customType:ParentRoom"
							)							
							if classof o.baseObject != Box and classof o.baseObject != Sphere and classof o.baseObject != Portal and classof o.baseObject != Capsule and classof o.baseObject != ParentRoom Then --o.name != "OgreMaxSceneSettings01"
							(
								--Valid objects are: Sphere, Box, Capsule, Editable Poly, Editable Mesh
								--messagebox ("Physics Exporter failed to recognize object " + o.name as string + " not possible to export")
								print ("Physics Exporter failed to recognize object " + o.name as string + " not possible to export")
								error = "True"
							)
						)
						
						
						int i
						i = 0
						for child in o.children do
						(
							i = i + 1
							settings.UserData += "\r\n" + "childNode" + (i as string) + ":" + child.name
							--settings.UserData += "\r\n" + "size:" + o.width as string + " " + o.height as string + " " + o.length as string + " "
						)
						
						--if (i) > 0 Then
						--(
						--	if o.static == false then
						--	(
						--		ResetTransform o
						--	)
						--)
							
							
							
						if classof o.material == Multimaterial do ( -- check if material assigned is multimaterial
							
								--for map = 1 to 3 do
								--print "CACAAAAAAA" + m.maps[2].bitmap as string
								try (
									texFileName = (o.material[1].maps[2].bitmap as string)
								)catch()	
								
								--print (material[1].maps[2].bitmap.coords.U_Tiling as string)
								try (
									settings.UserData += "\r\n" + "texU_Tiling:" + (o.material[1].maps[2].coordinates.U_Tiling as string)
									settings.UserData += "\r\n" + "texV_Tiling:" + (o.material[1].maps[2].coordinates.V_Tiling as string)

								)catch()
								
								try (
									ind = findString texFileName "\\"
   									while (ind != undefined) do (
	       								texFileName = substring texFileName (ind+1) (texFileName.count)
       									ind = findString texFileName "\\"
   									)
   								--print (o.name + " tex: " + texFileName as string) as string
								)catch()								

								if (o.static == true and o.objType == 3) do (
									setUserProp o "textureName" (texFileName as string)
									settings.UserData += "\r\n" + "texFileName:" + (texFileName as string)
								)
							--)
							--catch()	
						)

							
							
							--Add new line
						--settings.UserData += "\r\n"
						try(
							if o.particle then
							(
								settings.UserData += "\r\n" + "isParticle:yes"
    							settings.UserData += "\r\n" + "particleName:" + (getUserProp o "particleName" as string)
  
							)
							
						) catch ()
						
						--PARAMS			
						if o.static then
							settings.UserData += "\r\n" + "static:yes"
						else
						(
							if o.mass != 0 Then
							(
								settings.UserData += "\r\n" + "mass:" + o.mass as string
							)
							else
							(
								settings.UserData += "\r\n" + "density:" + o.density as string					
							)
							

						)
			
						if o.CCD do
							settings.UserData += "\r\n" + "CCD:yes"

						try (
							settings.UserData += "\r\n" + "angularDamping: " + o.angDamp as string
							settings.UserData += "\r\n" + "linearDamping: " + o.linDamp as string
							settings.UserData += "\r\n" + "restitution: " + o.restitution as string
							settings.UserData += "\r\n" + "staticFriction: " + o.staticFriction as string
							settings.UserData += "\r\n" + "dynamicFriction: " + o.dynamicFriction as string
						)
						catch(
							--print("Error in custAttributes.add")
							--error = "True"
						)	
												
						
						q = o.rotation
						p = o.position						
						--q = o.rotation
						if(o.parent != undefined) Then
						(
						--	q = o.parent.rotation * o.rotation
							settings.UserData += "\r\n" + "rotation:" + q.w as string + " " + q.x as string + " " + q.z as string + " " + (q.y) as string
							settings.UserData += "\r\n" + "position:" + " " + p.x as string + " " + p.z as string + " " + (q.y) as string
						) 
						else 
						(
							q = o.rotation

							settings.UserData += "\r\n" + "rotation:" + q.w as string + " " + q.x as string + " " + q.z as string + " " + (q.y *-1) as string
							settings.UserData += "\r\n" + "position:" + " " + p.x as string + " " + p.z as string + " " + (p.y *-1) as string
							
						)
						--ROTATION (And Add new line)	For some reason, 3ds doesn't have y-axis upwards. Which kinda screws things up.			     Also, the y-rotation is always the "wrong way"
						
			
						--Save Entity object property
						if o.objType == 1 do
							settings.UserData += "\r\n" + "bodyType:Body"
						--Save Actor object property
						if o.objType == 2 do
							settings.UserData += "\r\n" + "bodyType:Actor"
						if o.objType == 3 do
							settings.UserData += "\r\n" + "bodyType:Mesh"
						
						--obj=selection[1]
						--if (o.objType == 3 and o.static == true) do (
						--	alightMap=LightingMap()
						--	renderLightmap o alightMap 256 256 1 ("D:\\Devel\\#PROJECTS\\Ogre\\ApeEngineNew\\ApeLoader\\Media\\max models\\bakedTextures\\" + o.name + ".tga") false
						--)

						
						--If its Custom save type
						if o.type == 4 Then 
						(
							--Convex
							if o.customType == 1 do
								settings.UserData += "\r\n" + "physicsMeshType:Convex"
							--Triangle
							if o.customType == 2 do
								settings.UserData += "\r\n" + "physicsMeshType:Triangle"
						)
						
						if classof o.baseObject != ParentRoom and classof o.baseObject != Portal Then
						(
							settings.UserData += "\r\n" + "parentRoom:" + (getUserProp o "parentName" as string)
						)
						--if classof o.baseObject == ParentRoom Then
						--(
						--	settings.UserData += "\r\n" + "customType:ParentRoom"
						--)
						
						settings.UserData += "\r\n"
						
						
						if error == "True" Then
						(
							settings.UserData = "";
						)
	
						if o.name != "OgreMaxSceneSettings01" Then
						(
							if o.exportEnabled == false Then
							(
								settings.UserData = "";
							)
						)
					)					
	
				--)
			)
		)		
	--)
)

fn savePhysicsDataToFile = (

	--If Current Scene its not saved, then script objects arent either
	updateObject()
	if maxFilePath != "" and maxFileName != "" Then
	(
		out_name = maxFilePath + maxFileName + ".txt"
		
		out_file = createfile out_name
		
		try ( --Destroy previous dialogs
			format "loaderPath=%\n" sceneparams.loaderPath.text to:out_file
			format "scenePath=%\n" sceneparams.scenePath.text to:out_file
		)
		catch()

		for o in geometry do 
		(
			if o != undefined Then
			(
					fn GetGeometry o = (
					Superclassof o == Geometryclass and classof o != TargetObject )
					obj = o --pickobject filter:GetGeometry
					if isValidNode obj then
					(
						--tmesh = snapshotAsMesh obj
						
						if out_name != undefined then
						(
						
							format "name %\n" o.name to:out_file
							format "objType %\n" o.objType to:out_file
							format "type %\n" o.type to:out_file
							format "mass %\n" o.mass to:out_file
							format "density %\n" o.density to:out_file
							
							if (o.static == true) Then
								format "static %\n" "1" to:out_file
							else
								format "static %\n" "0" to:out_file
	
							if (o.CCD == true) Then
								format "CCD %\n" "1" to:out_file
							else
								format "CCD %\n" "0" to:out_file
							
							format "angDamp %\n" o.angDamp to:out_file
							format "linDamp %\n" o.linDamp to:out_file
							
							if (o.customShape != "") Then 
								format "customShape %\n" o.customShape to:out_file
							else
								format "customShape %\n" " " to:out_file
							
							format "customType %\n" o.customType to:out_file
							
							if (o.exportEnabled == true) Then
								format "exportEnabled %\n" "1" to:out_file
							else
								format "exportEnabled %\n" "0" to:out_file
							
				
						)
				
					)
					
			)
		)
		close out_file
	)
--	edit out_name
)

fn loadPhysicsDataFromFile = (
	
	--If Current Scene its not saved, then script objects arent either
	if(maxFilePath != "" and maxFileName != "") Then
	(
	
		in_name = maxFilePath + maxFileName + ".txt"
	
		if doesfileexist in_name == true Then
		(

			in_file = openFile in_name mode:"rt"
			
	    	l = readline in_file
			lf = filterString l "="
			
			print (lf[2] as string)

--			sceneparams.loaderPath.text = lf[2]

	    	l = readline in_file
			lf = filterString l "="

			print (lf[2] as string)				
			--sceneparams.scenePath.text = lf[2]
	
						
			while not eof in_file do
			(
				
		    	l = readline in_file
				lf = filterString l " "
				
				f_name = lf[2]
				
		    	l = readline in_file
				lf = filterString l " "
				
				f_objType = lf[2]
				
		    	l = readline in_file
				lf = filterString l " "
				
				f_type = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_mass = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_density = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_static = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_CCD = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_angDamp = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_linDamp = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_customShape = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_customType = lf[2]
		
		    	l = readline in_file
				lf = filterString l " "
		
				f_exportEnabled = lf[2]
				
				for o in geometry do 
				(
					if o != undefined Then
					(
						if o.name == f_name Then
						(
							o.objType = (f_objType as integer)
							o.type = (f_type as integer)
							o.mass = (f_mass as float)
							o.density = (f_density as float)
							
							if (f_static as integer) == 0 Then
								o.static = false
							else
								o.static = true
							
							if (f_CCD as integer) == 0 Then
								o.CCD = false
							else
								o.CCD = true
							
							o.angDamp = (f_angDamp as float)
							o.linDamp = (f_linDamp as float)
							o.customShape = (f_customShape as string)
							o.customType = (f_customType as integer)
							
							if (f_exportEnabled as integer) == 0 Then
								o.exportEnabled = false
							else
								o.exportEnabled = true
		
						)
		
					)
				)
				
			)
				
			close in_file
		)

	)
)


fn setRolloutControls = 
(
	if $ != undefined Then (
	
		local count = 0
		for o in $ do 
		(
			if o != undefined Then
			(
				count = count + 1
			)
		)
		--If only one node selected
		if count == 1 Then
		(
			if $ != undefined Then
			(

				error = "False"
				--Add custom attributes only to new nodes
				if (custAttributes.count $) == 0 Then
				(
					try (custAttributes.add $ newAttrib)
					catch(
						print("Error in custAttributes.add")
						error = "True"
					)
				)
				if (error) == "False" Then
				(
				
					--st = (getUserProp o "soundType" as string)
					--print st as string
					--if st == "custom" do
					--(
					sn = (getUserProp $ "soundName" as string)
					print sn as string
					--$.predefSounds = (sn as string)
				
					--(roomList.items) = deleteItem(roomList.items) roomList.items.count
					--($.PhysRollout.predefSounds.items) = append($.PhysRollout.predefSounds.items) (sn as string)				
				
					if ($.baseObject as string == "Editable Mesh") or 
						($.baseObject as string == "Editable Poly") Then 
					(				
						--$.PhysRollout.type.state = 4
						$.type = 4
						$.PhysRollout.customShape.text = $.name
					)
					else
					(
	--					$.PhysRollout.customType.enabled = false
						--$.customType = 0
						$.PhysRollout.customType.enabled = false
						
						if classof $.baseObject == Box Then
						(
							$.type = 1
							$.pivot = $.center
						)
						if classof $.baseObject == Sphere Then
						(
							$.type = 2
							$.pivot = $.center
						)
						if classof $.baseObject == Capsule Then
						(
							$.type = 3
							$.pivot = $.center
						)
					)
				)
			)
		)
	)
)

fn sceneFileSaved = 
(
	print ("Scene File Saved")
	savePhysicsDataToFile()
)
fn sceneReset = 
(
	print ("Scene File Reset")
)

--fn createJoint = (
--	myObject = Capsule Length:20 Radius:10
--)

--Global newAttrib	
--jointAttrib = attributes Physics
--(
--	parameters main rollout:JointsRollout 
--	(
--		jointType type:#integer ui:jointType default:1
--	)
--	
--	rollout JointsRollout "Physics - Joints"
--	(
--		radiobuttons jointType "Object Type" labels:#("a", "b") default:1
--		
--		on jointType changed v do
--		(
--			--updateObject()
--		)
--	)
--)
fn sceneFileOpened = (
	--print ("Scene File opened")
	
	--try ( --Destroy previous dialogs
	--	destroyDialog sceneparams
	--)
	--catch()
	--CreateDialog sceneparams
	sceneparams.scenePath.text = ""
	sceneparams.loaderPath.text = ""
	
	loadPhysicsDataFromFile()
)

fn cookMeshes scenePath = (
		if scenePath != "" Then
		(
--			batchFileName = loaderPath + "\data\batchConvert.bat"
			batchFileName = (scenePath as string)  + "\batchConv.bat "
			
			print batchFileName as string

			for o in geometry do 
			(
				if o != undefined Then
				(		
					if o.objType == 1 or o.objType == 2 Then
					(		
						if o.customType == 1 Then (
							t = "Convex"
						)
						else (
							t = "Triangle"
						)
						try (
							--shellLaunch batchFileName  (o.name + ".mesh " + t)
							cmdText = batchFileName + (o.name + ".mesh " + t)
							print cmdText
							DOSCommand cmdText

						)
						catch()
					)
				)
			)
			
		)
		else
		(
			messagebox ("You must select the loader path first")
		)

)


--Global newAttrib	
newAttrib = attributes Physics
(
	parameters main rollout:PhysRollout
	(
		--For saving
		type type:#integer ui:type default:1
		static type:#boolean ui:static default:true --sacar
		CCD type:#boolean ui:CCD default:false

		predefPhysics type:#string ui:predefPhysics default:""
		
		mass type:#float ui:mass default:10
		density type:#float ui:density default:0
		angDamp type:#float ui:angDamp default:0.05
		linDamp type:#float ui:linDamp default:0.0
		restitution type:#float ui:restitution default:0.8
		staticFriction type:#float ui:staticFriction default:1.0
		dynamicFriction type:#float ui:dynamicFriction default:1.0
		
		objType type:#integer ui:objType default:2
		customShape type:#string ui:customShape default:""
		customType type:#integer ui:customType default:2
		exportEnabled type:#boolean ui:exportEnabled default:true
		
		soundType type:#integer ui:soundType default:1
		soundSize type:#integer ui:soundSize default:1
		predefSounds type:#string ui:predefSounds default:"stone"
		
		particle type:#boolean ui:particle default:false
		particleName type:#string ui:particleName default:""


	)
	
	rollout PhysRollout "Ape Engine"
	(
		checkbox exportEnabled "Export"
		
		group "Bodies"
		(

			--User input widgets
			radiobuttons objType "Object Type" labels:#("Body", "Actor","Mesh") default:2
			radiobuttons type "Collision mesh" labels:#("Box","Sphere","Capsule","Custom (.nxs file)") default:1 enabled:true
	
			edittext customShape "Custom Shape" enabled:false
			radiobuttons customType "Custom Type:" labels:#("Convex", "Triangle") default:2 enabled:false
			
			checkbox static "Static" default:true
			checkbox CCD "Use CCD"

			combobox predefPhysics "Presets" items:#("Default_Small","Default_Big") default:1 enabled:true height:3
			--height:3
						
	
			spinner mass "Mass" type:#float range:[0,300000,10]
			spinner density "Density" type:#float range:[0,30000,0]
			spinner restitution "Restitution" type:#float range:[0,1,0.1]
			spinner staticFriction "Static Friction" type:#float range:[0,1,0.1]
			spinner dynamicFriction "Dyn. Friction" type:#float range:[0,1,0.1]
			spinner angDamp "Angular damp" type:#float range:[0,50,0.05]
			spinner linDamp "Linear damp" type:#float range:[0,50,0.0]

			button center "Center pivot-point"
			--button erase "Erase params"
		)
		group "Sounds"
		(
			radiobuttons soundType "Sound Type:" labels:#("Predefined", "Custom") default:1 enabled:true
			radiobuttons soundSize "Size:" labels:#("Light", "Medium", "Heavy") default:1 enabled:true
			--combobox predefSounds "Sound" items:#("Wood", "Stone", "Glass", "Metal") enabled:true
			--combobox predefSounds "Sound" items:#() enabled:true

			--nom = "asd"
			--try (nom = (getUserProp $ "soundName" as string) )
			--catch(nom = "")
			
			combobox predefSounds "Sound" items:(
			
				for o in Geometry
					where classof o.baseObject != undefined collect (getUserProp $ "soundName" as string)
			)
			
			button addSound "Add Custom Sound" enabled:true
		)
		group "Particle"
		(
			checkbox particle "Is Particle" default:false
			edittext particleName "Particle Script Name" enabled:true

		)
		
		on particle changed v do
		(
			setUserProp $ "isParticle" ("true" as string)
			particleName.enabled = true
			updateObject()
		)
		
		on particleName changed v do
		(
		    setUserProp $ "particleName" (v as string)
			updateObject()
		)	
		
		--group "Joints"
		--(		
		--	radiobuttons jointType "Joint Type" labels:#("a", "b") default:1
		--)

		on predefPhysics selected v do
		(
			
			case v of
			(
				1: 	(
						mass.value = (20 as float)
						density.value = (0 as float)
						restitution.value = (0.2 as float)
						staticFriction.value = (1.0 as float)
						dynamicFriction.value = (1.0 as float)
						angDamp.value = (0.05 as float)
						linDamp.value = (0.0 as float)
						
					)

			)			
		)
			
		on predefSounds selected v do
		(
			
			--sname = (getUserProp $ "soundName" as string)
			
			--if sname != "" do
			--( predefSounds.selected
				--print ("holaaa " + (predefSounds.items[v] as string) )

				setUserProp $ "soundName" ((predefSounds.items[v] as string) )

			--)
			--print "no"
			updateObject()
		)
		
		on soundSize changed v do
		(
			case v of
			(
				1: 	(
						setUserProp $ "soundSize" "light"
					
					)
				2: (
						setUserProp $ "soundSize" "medium"
				
				
				   )
				3: (
						setUserProp $ "soundSize" "heavy"
					)

			)
			updateObject()
		)
		
		on addSound pressed do
		(
			--for i = 1 to (predefSounds.items.count) do
			--(
			--	if 
			
				(predefSounds.items) = append(predefSounds.items) (predefSounds.text)
			--)
				setUserProp $ "soundName" ((predefSounds.text as string) )
			
			updateObject()
		)
		
		on soundType changed v do
		(
		
			case v of
			(
				--Predefined
				1: 	(soundSize.enabled = true
	 				addSound.enabled = false
				
					for i = 1 to (predefSounds.items.count) do
					(
						(predefSounds.items) = deleteItem(predefSounds.items) predefSounds.items.count
					)
					
					
					(predefSounds.items) = append(predefSounds.items) ("bodyfall")
					(predefSounds.items) = append(predefSounds.items) ("cloth")
					(predefSounds.items) = append(predefSounds.items) ("earth")
					(predefSounds.items) = append(predefSounds.items) ("glass")
					(predefSounds.items) = append(predefSounds.items) ("grass")
					(predefSounds.items) = append(predefSounds.items) ("metal")
					(predefSounds.items) = append(predefSounds.items) ("organic")
					(predefSounds.items) = append(predefSounds.items) ("stone")
					(predefSounds.items) = append(predefSounds.items) ("water")
					(predefSounds.items) = append(predefSounds.items) ("wood")

						
					setUserProp $ "soundType" "predefined"
					
					)
				--Custom
				2: 	(soundSize.enabled = false
					addSound.enabled = true
					
					for i = 1 to (predefSounds.items.count) do
					(
						(predefSounds.items) = deleteItem(predefSounds.items) predefSounds.items.count
					)
					
					setUserProp $ "soundType" "custom"

					)
			)
			updateObject()
			
		)	
		
		on exportEnabled changed v do
		(
			updateObject()
		)
		on angDamp changed v do
		(
			updateObject()
		)
		on linDamp changed v do
		(
			updateObject()
		)

		on CCD changed v do
		(
			updateObject()
		)
		on mass changed v do
		(
			updateObject()
		)	
		on density changed v do
		(
			updateObject()
		)	
		on static changed v do
		(
			updateObject()
		)	
		
		on customType changed v do
		(
			updateObject()
		)			
		on customShape changed v do
		(
			updateObject()
		)		
		on objType changed v do
		(
			updateObject()
		)
		
		on type changed v do
		(
			case v of
			(
				--Box
				1: 	(customShape.enabled = false
					center.enabled = true
					customType.enabled = false )
				--Sphere
				2: 	(customShape.enabled = false
					center.enabled = true
					customType.enabled = false )
				--Capsule
				3: 	(customShape.enabled = false
					center.enabled = true
					customType.enabled = false )

				--Custom
				4: 	(--customShape.enabled = true
					center.enabled = false
					density.value = 0
					customType.enabled = true
					customShape.text = $.name )

			)
			updateObject()
		)
		
		on static changed v do
		(
			if v then
			(
				mass.enabled = false
				density.enabled = false
			)
			else
			(
				mass.enabled = true
				density.enabled = true
			)
			updateObject()
		)
		
		--Center pivot-point
		on center pressed do
		(
			$.pivot = $.center
			updateObject()
		)
		
	)
	
)

fn setParentToObjects = --parentName
(
	
	for o in $ do 
	(
		--roomList.selected
		setUserProp o "parentName" "default"
		print ("setting ParentToObjects" + o.name as string)
		if classof o.baseObject != ParentRoom and classof o.baseObject != Portal Then
		(
			setUserProp o "parentName" roomList.selected --parentName
		)
	)
)


fn renderLightmap obj currentMapType Xsize Ysize channel fullFileName virtualFrameBufferState =
(
fPath=getFilenamePath fullFileName
fName=getFilenameFile fullFileName
fType=getFilenameType fullFileName
bi = obj.INodeBakeProperties

--currentMapType = LightingMap()
--alightMap=LightingMap()

--currentMapType.enabled = true


currentMapType.outputSzX=Xsize
currentMapType.outputSzY=Ysize
--currentMapType.filename=fName
--currentMapType.filename=""
--currentMapType.fileType=fType

currentMapType.filename = (obj.name) -- + "_lm"
currentMapType.filetype = ".tga"
currentMapType.elementName = "" --_lm

--currentMapType.autoSzOn = true
--currentMapType.bright = color 255 255 255 0
--currentMapType.dark = color 0 0 0 0
--currentMapType.elementName = "LightingMap"
--currentMapType.falloff = 1.0
--currentMapType.maxDistance = 0.8
--currentMapType.samples = 16
--currentMapType.spread = 0.8
--currentMapType.enabled = true
--currentMapType.targetMapSlotName = "LightingMap"
--currentMapType.directOn = true
--currentMapType.indirectOn = true
--currentMapType.shadowson = true
--currentMapType.outputszx =TexWidth
--currentMapType.outputszy =TexHeight
--currentMapType.enabled = true
--currentMapType.filename = ($.name + "_" + maptype)
--currentMapType.filetype = ".tga"
--currentMapType.addBakeElement BakeObjLight

--BakeProj = obj.INodeBakeProjProperties
--BakeProj.enabled = false-- Enable/Disable Projection Baking for the node
--BakeProj.projectionMod = undefined -- Get/Set the Projection Modifier
--BakeProj.projectionModTarget =""-- Get/Set the Projection Modifier Target
--BakeProj.cropAlpha = true -- Get/Set whether Alpha will be cropped

bi.removeAllBakeElements()

--bi.path = "C:\\"

bi.addBakeElement currentMapType
bi.bakeChannel=channel
bi.bakeEnabled = true

--render rendertype:#bakeSelected outputwidth:Xsize outputheight:Ysize outputfile:(fPath+fName+fType) vfb:virtualFrameBufferState
--local bm = bitmap Xsize Ysize filename:( (fPath+fName+fType) as string)

--render rendertype:#bakeSelected outputwidth:Xsize outputheight:Ysize to:bm vfb:virtualFrameBufferState

--bi.removeAllBakeElements()
--bi.bakeEnabled = false

format "rendering node:% channel:%\n" obj.name bi.bakeChannel
)

fn bake_AO_maps obj _size _quality=
(
	tex_size = _size
	--obj = selection[1]
	--obj.removeAllBakeElements()

	--bi = obj.INodeBakeProperties
	ao_bake = AmbientOcclusionBakeElement()
	ao_bake.outputSzX =    tex_size
	ao_bake.outputSzY =    tex_size
	ao_bake.autoSzOn = false
	ao_bake.bright = color 255 255 255 0;
	ao_bake.dark = color 0 0 0 0;
	--ao_bake.backgroundColor = color 0 0 0 0;
	--ao_bake.elementName = "Ambient Occlusion"
	ao_bake.falloff = 1.0
	ao_bake.maxDistance = 0.0
	ao_bake.samples = 2+_quality*120 --16
	ao_bake.spread = 40.1 - _quality*40 --0.8
	ao_bake.enabled = true
	--ao_bake.fileType = GetDir #image + "_renderToClipboard3.bmp" --appearently the target filename/path
	--ao_bake.fileType = "C:\\" + "file_renderToClipboard3.bmp" --appearently the target filename/path
	
	ao_bake.filename = (obj.name) -- + "_lm"
    ao_bake.filetype = ".tga"
    ao_bake.elementName = "" --_lm

	
	-- Baking job
	bake = obj.INodeBakeProperties
	bake.bakeChannel = 2
	bake.nDilations         = 2 -- (Pading)
	bake.flags             = 1 --bit 1 of flag will be set to signify map channel conflict
	bake.bakeEnabled     = true
	bake.removeAllBakeElements()
	bake.addBakeElement ao_bake
	--select obj
	
	--render rendertype:#bakeSelected outputwidth:tex_size outputheight:tex_size vfb:false
	--render rendertype:#bakeSelected outputwidth:tex_size outputheight:tex_size vfb:false

	--copy to clipoard and delete temp image
	--theFileName = ao_bake.fileType --define a temp.file name
	
	--clipboardClass = dotNetClass "System.Windows.Forms.Clipboard" --create a Clipboard dotNetClass
	--theImage = dotNetClass "System.Drawing.Image" --create an Image dotNetClass
	--theBitmap = theImage.FromFile theFileName --get the saved image from file as bitmap
	--clipboardClass.setImage theBitmap --copy the image to clipboard
	--theBitmap.Dispose() --release the bitmap 
	--deleteFile theFileName --delete the temp. file
	--clipboardClass.ContainsImage() --return true if the clipboard contains image
	
	--remove traces
	--bake.removeAllBakeElements()
	--bake.bakeEnabled = false
	--obj.removeAllBakeElements()
)


--Global sceneparams
rollout sceneparams "Physics Exporter for OgreMax" width:300
(
	
	--parameters main rollout:sceneparams 
	--(
	--)
	--group "Bodies/Actors"
	--(
	checkbox gravity "Gravity" checked:true
	checkbox floor "Floor" checked:false
	combobox controller "Controller" items:#("none", "accumulator") height:3 selection:2
	button createparams "Create Params"
	edittext scenePath "Scene path"
	button browseScenePath "Browse"
	edittext loaderPath "Loader Dir Path"
	button browseLoaderPath "Browse"
	button updateSceneObjects "Save"
	button generateNXSFiles "Cook Phisycs Meshes"
	button bakeLightMaps "Bake Lightmaps"
	button bakeAO "Bake AO"

	--button bakeAllObjects "Bake all objects"
	

	button runScene "Create Scene"
	
	listbox roomList "Rooms:" width:90 height:10 items:(
		for o in Geometry
			where classof o.baseObject == ParentRoom collect o.name
	)
	button setParentToObjects "Set parent Room to selected geometry"
	button refreshParents "Refresh parent list"

	--listbox portalList "Portals:" width:90 height:10 items:(
	--	for o in Geometry
	--		where classof o.baseObject == Portal collect o.name
	--)
	
	button setupPortalsAndRooms "Connect Rooms (must select 2 rooms and 1 portal first)"

	button setExteriorPortal "Exterior Portal"
	
	button setObjectToDefaultZone "Set to default Zone"

	button setActors "Convert selected to Actor"
	button setBody "Convert selected to Body"
	button setMesh "Convert selected to Mesh"
	button renameObjects "Rename Objects"
	
	button updateScript "Update Object (script)"	

	--(
	--	for o in Geometry
		--(
		--	if classof o.baseObject == ParentRoom Then
		--	(
	--			collect o.name
		--	)
		--)
	--)

	on bakeLightMaps pressed do
	(
		for o in $ do 
		(	
			--print o.name
			--if classof o.baseObject == EditableMesh Then -- and classof o.baseObject != Portal 
			--(
			try (
				tex = (getUserProp o "texFileName" as string)
				--print tex as string
				if (tex != "") do (

					--alightMap=CompleteMap()
					--alightMap=SpecularMap()
					--alightMap=DiffuseMap()
					--alightMap=ShadowsMap()
 					alightMap=LightingMap()
					--alightMap=NormalsMap()
					--alightMap=BlendMap()					
					--alightMap=AlphaMap()
					--alightMap=HeightMap()					
					
					renderLightmap o alightMap 256 256 2 ("D:\\Devel\\#PROJECTS\\Ogre\\ApeEngineNew\\ApeLoader\\Media\\max models\\bakedTextures\\" + o.name + ".tga") false
				)
			) catch()
			--)
		)
	)
	
	on bakeAO pressed do
	(
		for o in $ do 
		(	
			bake_AO_maps o 128 1.6 --256 0.8
		)
	)
	
	--on bakeAllObjects pressed do
	--(
	--	for o in Geometry do 
	--	(
			--print o.name
			--if classof o.baseObject == EditableMesh Then -- and classof o.baseObject != Portal 
			--(
	--		try (
	--			tex = (getUserProp o "texFileName" as string)
				--print tex as string
	--			if (tex != "") do (
	--				alightMap=LightingMap()
	--				renderLightmap o alightMap 256 256 2 ("D:\\Devel\\#PROJECTS\\Ogre\\ApeEngineNew\\ApeLoader\\Media\\max models\\bakedTextures\\" + o.name + ".tga") false
	--			)
	--		) catch()		
	--	)
	--)

	on updateScript pressed do
	(
						--custAttributes.add o newAttrib #Unique
						if (custAttributes.count $) > 0 Then
						(
							try (custAttributes.delete $ 1
								custAttributes.add $ newAttrib
								print "update done! " + (custAttributes.count $) as string
							)
							catch(
								print("Error in custAttributes.delete")
								error = "True"
							)					
	
						) 
	)
	
	on setObjectToDefaultZone pressed do
	(
		for o in $ do 
		(
			--roomList.selected
			setUserProp o "parentName" "default"
			--print ("setting ParentToObjects" + roomList.selected)
			if classof o.baseObject != ParentRoom and classof o.baseObject != Portal Then
			(
				setUserProp o "parentName" "defaultZone"
			)
		)	
	)

	on setActors pressed do
	(
		if $ != undefined Then
		(
	

			for o in $ do 
			(
						error = "False"
	
						--custAttributes.add o newAttrib #Unique
						if (custAttributes.count o) == 0 Then
						(
							try (custAttributes.add o newAttrib)
							catch(
								print("Error in custAttributes.add")
								error = "True"
							)					
	
						)
						
						if (error) == "False" Then
						(
				
							o.objType = 2
							
						)					
							
			)
	
		)
	
	)
	
	on setMesh pressed do
	(
		if $ != undefined Then
		(
	

			for o in $ do 
			(
						error = "False"
	
						--custAttributes.add o newAttrib #Unique
						if (custAttributes.count o) == 0 Then
						(
							try (custAttributes.add o newAttrib)
							catch(
								print("Error in custAttributes.add")
								error = "True"
							)					
	
						)
						
						if (error) == "False" Then
						(
				
							o.objType = 3
							
						)					
							
			)
	
		)
	
	)	

	on renameObjects pressed do
	(
	
		rollout rename_rollout "Enter New Base Name"
		(
			edittext base_name ""
			button rename_them "RENAME SELECTED OBJECTS..."
			on rename_them pressed do
			(
				if base_name.text != "" then
					for i in selection do i.name = uniquename base_name.text

			)
		)

		createDialog rename_rollout 250 50
	)	

	
	on setBody pressed do
	(
		if $ != undefined Then
		(
	

			for o in $ do 
			(
						error = "False"
	
						--custAttributes.add o newAttrib #Unique
						if (custAttributes.count o) == 0 Then
						(
							try (custAttributes.add o newAttrib)
							catch(
								print("Error in custAttributes.add")
								error = "True"
							)					
	
						)
						
						if (error) == "False" Then
						(
				
							o.objType = 1
							
						)					
							
			)
	
		)
	
	)
	
	on setExteriorPortal pressed do
	(
		if ($.count == 2) Then
		(
			roomOne = ""
			count = 0
			for o in $ do
			(
				if classof o.baseObject == ParentRoom Then
				(
					count = count + 1
					if (count == 1) Then
					(
						roomOne = o.name
						print("setting room 1")
					)
				)
			)
			print(roomOne)	

			for o in $ do
			(
				if classof o.baseObject == Portal Then
				(
					setUserProp o "parentRoom1" roomOne 
					setUserProp o "parentRoom2" "defaultZone" 
				)
			)
			
		)
	)

	
	on setupPortalsAndRooms pressed do
	(
		if ($.count == 3) Then
		(
			roomOne = ""
			roomTwo = ""
			count = 0
			for o in $ do
			(
				if classof o.baseObject == ParentRoom Then
				(
					count = count + 1
					if (count == 1) Then
					(
						roomOne = o.name
						print("setting room 1")
					)
					if (count > 1) Then
					(
						roomTwo = o.name
						print("setting room 2")						
					)	
				)
			)
			print(roomOne)	
			print(roomTwo)	
			
			for o in $ do
			(
				if classof o.baseObject == Portal Then
				(
					setUserProp o "parentRoom1" roomOne 
					setUserProp o "parentRoom2" roomTwo 
				)
			)
			
		)
	)
	
	on refreshParents pressed do
	(
		for o in Geometry do 
		(
			if classof o.baseObject == ParentRoom Then
			(
				--roomList.items collect o.name
				--for i = 1 to (roomList.items.count) do
				--(
				--	(roomList.items) = deleteItem(roomList.items) 1
				--)
				(roomList.items) = deleteItem(roomList.items) roomList.items.count

				(roomList.items) = append(roomList.items) (o.name)
					
			)
		)
	)
	
	on setParentToObjects pressed do
	(
		--parentObject = "Parent Room01"
		--parentObject = roomList.selected
		--setParentToObjects --parentObject
		--print parentObject
		roomObj = undefined
		for o in $ do 
		(
			if classof o.baseObject == ParentRoom Then
			(
				--setUserProp o "parentName" roomList.selected --parentName
				roomObj = o
				print roomObj.name as string
			)
			
		)
		camObj = undefined
		for o in $ do 
		(
   		    --print o.baseObject as string
			if o.baseObject as string == "Target Camera" Then --classof 
			(
				setUserProp roomObj "cameraName" o.name --parentName
				camObj = o
				--print camObj.name as string
			)
			
		)
		
		for o in $ do 
		(
			--roomList.selected
			setUserProp o "parentName" "default"
			--print ("setting ParentToObjects" + roomList.selected)
			if classof o.baseObject != ParentRoom and classof o.baseObject != Portal Then
			(
				setUserProp o "parentName" roomList.selected --parentName
			)

		)		
		
	)	

	on browseScenePath pressed do
	(
		path = getSavePath caption:"Select path where .scene was saved" initialDir:"H:\Devel\#PROJECTS\Ogre\PenaltyGame\Media\Models\Penalty"
		if path  != undefined then
		(
			scenePath.text = path
		)
		
	)

	on browseLoaderPath pressed do
	(
		path = getSavePath caption:"Select Dir where Loader.exe is located" initialDir:"H:\Devel\#PROJECTS\Ogre\PenaltyGame\bin\debug"
		if path  != undefined then
		(
			loaderPath.text = path
		)
	)
	
	--on browseFlourPath pressed do
	--(
	--	path = getOpenFileName caption:"Select path where Flour.exe is located" initialDir:"$scripts" types:"*.exe"
	--	if path  != undefined then
	--	(
	--		flourPath.text = path
	--	)
	--)
	
	on generateNXSFiles pressed do
	(
		updateObject()
		cookMeshes scenePath.text
	)
	
	on runScene pressed do
	(
		updateObject()
		if loaderPath.text != "" Then
		(
			--batchConvertPath = loaderPath.text + "\data\batchConvert.bat"
			--shellLaunch batchConvertPath ""
			if queryBox "Do you want to cook the meshes?" beep:true then
			(
				cookMeshes loaderPath.text
			)
			exeName = loaderPath.text + "\NxOgreLoaderDemo.exe"
			shellLaunch exeName  ""
		)
		else
		(
			messagebox ("You must select the loader path first")
		)			
	)
	
	--on saveSceneData pressed do
	--(
	--	savePhysicsDataToFile()
	--)
	
	--on loadSceneData pressed do
	--(
	--	loadPhysicsDataFromFile()
	--)
	
	on updateSceneObjects pressed do
	(
		helpMenu = menuMan.findMenu "OgreMax"
		if helpMenu == undefined Then
		(
			messagebox ("PhysX Exporter failed to find OgreMax Plug-in!")
			--MessageBox ("PhysX Exporter failed to find OgreMax Plug-in!")
		)
		else (
			--menuMan.createSubMenuItem "name" helpMenu 
			--if menuMan.registerMenuContext 0x246c6dbe then
			--(

			--	local sepItem = menuMan.createSeparatorItem()
			--	local testItem = menuMan.createActionItem "PhysX Exporter" "Menu Test"
				
			--	helpMenu.addItem sepItem -1
			--	helpMenu.addItem testItem -1
				
			--	menuMan.updateMenuBar()
			--)
		)
		
		updateObject()
		savePhysicsDataToFile()
			
	)
	
	--on createShape pressed do
	--(
		--Box
	--	if shapeType.state == 1 then
	--	(
	--		myObject = Box Length:20 Width:20 Height:20
	--	)
		--Sphere
	--	else if shapeType.state == 2 then
	--	(
	--		myObject = Sphere radius:20
	--	)
		--Capsule
	--	else if shapeType.state == 3 then
	--	(
	--		myObject = Capsule Length:20 Radius:10
	--	)
	--)		
	
	on createparams pressed do
	(
		--Add collsions and new lines
		--params = path.text + "\r\n"
		--params += meshes.text + "\r\n"
		params = ""
		--Misc
		if gravity.checked do
			params += "gravity: yes"
		if floor.checked do
			params += ", floor: yes"
		--if renderer.text != "none" do
		--	params += ", renderer: " + renderer.text
		if controller.text != "none" do
			params += ", controller: " + controller.text

		params += "\r\n"
		
		t = ogremax.GetSceneSettings()
		t.UserData = params
	)
)

--Create the Scene configuration dialog
CreateDialog sceneparams
--custAttributes.add sceneparams sceneAttrib
try(
sceneparams.scenePath.text = ""
sceneparams.loaderPath.text = ""
) catch ()