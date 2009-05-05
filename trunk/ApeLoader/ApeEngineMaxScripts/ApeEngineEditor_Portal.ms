plugin simpleObject Portal

name:"Portal"

classID:#(644423,874564)

category:"Ape Engine Entities" --Scripted Primitives
( 

	local plane1
	parameters main rollout:params
	(
		length type:#worldUnits ui:length default:1E-3
		width type:#worldUnits ui:width default:1E-3
		--height type:#worldUnits ui:height default:1E-3

	)

	rollout params "Two Faces Parameters"
	(
		--spinner height "Height" type:#worldUnits range:[1E-3,1E9,1E-3]
		spinner width "Width" type:#worldUnits range:[1E-3,1E9,1E-3]
		spinner length "Length" type:#worldUnits range:[-1E9,1E9,1E-3]
	)

	on buildMesh do
	(
		--setMesh mesh \
		--verts:#([0,0,0],[width,0,0],[width,depth,0],[0,depth,0]) \
		--faces:#([3,2,1], [1,4,3])
		--extrudeFace mesh #(1,2) (height * 0.5) 40 dir:#common
		--extrudeFace mesh #(1,2) (height * 0.5) 50 dir:#common
		--if box1 == undefined then
		plane1 = createInstance plane
		
		plane1.width = width
		plane1.length = length
		
		mesh = plane1.mesh
	)
	
	tool create
	(
		on mousePoint click do
		case click of
		(
			1: nodeTM.translation = gridPoint
			3: (#stop)
		)
	
		on mouseMove click do
		case click of
		(
			2: (width = abs gridDist.x;length = abs gridDist.y)
			--3: height = gridDist.z
		)
	
	)

)