#include <stdio.h>
#include <omp.h>
#include <climits>
#include "vec3.h"
#include "myList.h"
#include "sphere.h"
#include "png.hpp"
#include <Windows.h>
#include "color.h"
#include "RayTrace.h"

List<Object*> sphereList;
Scene myRender = Scene();
FixedOrthographicCamera myCam;



Point EyePosition =Point(0., 0., -100.,0.); //eye position is in the center of the screen output
Vec3 LookAt = Vec3(0.,0.,0.); //look at origin

int setSceneOne(int argv) {
    //Get spheres

	SphereObject* sphere1 = new SphereObject();
	sphere1->radius = 100.0f;
	sphere1->position.x = 200.0f;
	sphere1->position.y = 200.0f;
	sphere1->position.z = 1200.0f;
	sphere1->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

		// GREEN Sphere
		SphereObject* sphere2 = new SphereObject();
		sphere2->radius = 300.0f;
		sphere2->position.x = 750.0f;
		sphere2->position.y = 500.0f;
		sphere2->position.z = 1600.0f;
		sphere2->color = Color(0.0f, 1.0f, 0.0f, 1.0f);

		// BLUE TRIANGLE
		SphereObject* sphere6 = new SphereObject();
		sphere6->radius = 250.0f;
		sphere6->position.x = 1500.0f;
		sphere6->position.y = 700.0f;
		sphere6->position.z = 1200.0f;
		sphere6->color = Color(1.0f, 1.0f, 0.0f, 1.0f);

		myRender.objects.AddValue(sphere1);
		myRender.objects.AddValue(sphere2);
		myRender.objects.AddValue(sphere6);

		
			//BLUE SPHERE.
			SphereObject* sphere4 = new SphereObject();
			sphere4->radius = 50.0f;
			sphere4->position.x = 500.0f;
			sphere4->position.y = 400.0f;
			sphere4->position.z = 1200.0f;
			sphere4->color = Color(0.0f, 0.0f, 1.0f, 1.0f);
			myRender.objects.AddValue(sphere4);
	

				//A GREEN PLANE
				TriangleObject* t2 = new TriangleObject();
				t2->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
				t2->a = Point(1920., 0., 1700., 0.);
				t2->b = Point(0., 0., 1700., 0.);
				t2->c = Point(1920., 1080., 1700., 0.);

				TriangleObject* t3 = new TriangleObject();
				t3->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
				t3->a = Point(0., 0., 1700., 0.);
				t3->b = Point(1920., 1080., 1700., 0.);
				t3->c = Point(0., 1080., 1700., 0.);

				myRender.objects.AddValue(t2);
				myRender.objects.AddValue(t3);
		
			//Get lights
	
	

    return 0;
}


png::rgb_pixel Trace(int i, int j,Light * aLight)
{

	Ray thisRay = myCam.GetRay(i,j);

    float minDistance = INFINITY;
	RayHitInfo myMan;
	myCam.position = Point(0., 0., 0., 0.);
	if (RayTrace(&myCam,myRender.objects,aLight, thisRay, myMan, 5))
	{

		Color myPixel = ConvertColor(myMan.pixel);
		return png::rgb_pixel(myPixel.r * 255.,myPixel.g * 255., myPixel.b * 255.);
	}

	else
		return png::rgb_pixel(0., 0., 0.);


}

int main() {
    int w, h;
    w = 1920;
    h = 1080;
	Light* light = new Light(POINT_LIGHT, Point(300.0f, 300.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f, 0.0f), Color(1.0f, 1.0f, 1.0f, 1.0f));
	light->SetIntensity(1.0f);
	light->SetSpecularAttributes(60.0f, Color(1.0f, 1.0f, 1.0f, 1.0f));
	light->direction.Normalize();
    omp_set_num_threads(8);

    png::image<png::rgb_pixel> image(w, h);
	int c = 3;
	setSceneOne(c);
	printf("Tracing rays.\n");
    #pragma omp parallel for
    for (int j = 0; j < h; j++) {
	   for (int i = 0; i < w; i++) {
		   image[j][i] = Trace(i, j, light);
	   }
    }
	printf("Image saved to cs419_tyrrella_final\Raytracing\Debug\test.png. ");
	image.write("test.png");
	Sleep(6000);

}