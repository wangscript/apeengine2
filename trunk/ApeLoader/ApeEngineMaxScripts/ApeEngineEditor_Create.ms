macroScript ApeEngine_Create category:"ApeEngineEditor" tooltip:"Create"

Icon:#("SchematicView",2)
(


	parentObj = undefined
	for o in Geometry do 
	(
		--Iterate parent rooms
		print(classof o.baseObject)
		if classof o.baseObject == ParentRoom Then
		(		
			parentObj = o
			setUserProp o "ParentRoom" true
			print("Parent Room found and set")
			
			--For each parent iterate childs
			for child in Geometry do 
			(
				--skip parent rooms
				if classof child.baseObject != ParentRoom Then
				(
					setUserProp o "ParentRoom" false
					setUserProp o "ChildObject" true
					--print("setting child objects")
					--boolobj.createbooleanobject parentObj child 1 2
					--boolobj.setboolop parentObj 1
					--addmodifier parentObj (edit_mesh())
					--select parentObj 
					--max modify mode
					--subobjectlevel = 1
					--meshops.weld parentObj.modifiers[1]
					--max select none
					--subobjectlevel = 0
					
				)
			)
			
		)		
	
	)
	
)

