import ocl
import camvtk
import time
import vtk
import datetime
import math

def drawVertex(myscreen, p, vertexColor, rad=1):
    myscreen.addActor( camvtk.Sphere( center=(p.x,p.y,p.z), radius=rad, color=vertexColor ) )

def drawEdge(myscreen, e, edgeColor=camvtk.yellow):
    p1 = e[0]
    p2 = e[1]
    myscreen.addActor( camvtk.Line( p1=( p1.x,p1.y,p1.z), p2=(p2.x,p2.y,p2.z), color=edgeColor ) )

def drawFarCircle(myscreen, r, circleColor):
    myscreen.addActor( camvtk.Circle( center=(0,0,0), radius=r, color=circleColor ) )

if __name__ == "__main__":  
    print ocl.revision()
    myscreen = camvtk.VTKScreen()
    
    vd = ocl.VoronoiDiagram(100)
    
    #p=ocl.Point(60,60)
    vd.addVertexSite( ocl.Point(61,61) )
    print "PYTHON VERTEX SITE DONE ()"
    #p=ocl.Point(-10,-10)
    vd.addVertexSite( ocl.Point(0,-20) )
    #vd.addVertexSite( ocl.Point(20,20) )
    
    far = vd.getFarRadius()
    drawFarCircle(myscreen, far, camvtk.pink)
    drawFarCircle(myscreen, 3*far, camvtk.orange)
    
    for v in vd.getGenerators():
        drawVertex(myscreen, v, camvtk.green, 2)
        
    for v in vd.getVoronoiVertices():
        drawVertex(myscreen, v, camvtk.red, 1)
    
    for v in vd.getFarVoronoiVertices():
        drawVertex(myscreen, v, camvtk.pink, 10)
    
    vde = vd.getVoronoiEdges()
    print " got ",len(vde)," Voronoi edges"
    for e in vde:
        pass
        drawEdge(myscreen,e, camvtk.cyan)
    
    #dle = vd.getDelaunayEdges()
    #print " got ",len(dle)," Delaunay edges"
    #for e in dle:
    #    drawEdge(myscreen,e, camvtk.red)
    
    myscreen.camera.SetPosition(0.1, 0, 1100)
    myscreen.camera.SetFocalPoint(0, 0, 0)
    #camvtk.drawArrows(myscreen,center=(-0.5,-0.5,-0.5))
    camvtk.drawOCLtext(myscreen)
    myscreen.render()    
    myscreen.iren.Start()
