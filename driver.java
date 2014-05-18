public class driver {

	public static void main(String args[]){
		//create  an air traffic control. There is only one per airport
		AirTrafficControl atc = new AirTrafficControl();
		//create multiple runways, all of which are linked to the singular air traffic control
		//we will mainly  use one runway for this demonstration in order to keep traffic at least a little congested
		
		Runway runway = new Runway(atc,1,3);
		//other runways are used just to show the functionality of the emergency state
		atc.addRunway(runway);
		Runway runway1 = new Runway(atc,2, 1);
		atc.addRunway(runway1);
		Runway runway2 = new Runway(atc,3, 2);
		atc.addRunway(runway2);
		//create runway personnel that maintain the surface of the runway
		RunwayPersonnel rwp1 = new RunwayPersonnel("John", 1, "Surface Maintainer", runway);
		RunwayPersonnel rwp2 = new RunwayPersonnel("Dave", 2, "Surface Maintainer", runway);
		//test to make sure guard condition is working, only surface maintainers maintain surface
		RunwayPersonnel rwp3 = new RunwayPersonnel("Joe", 3, "Manager", runway);
		//create some planes, all of which use the same runway and  the single air traffic control
		Plane plane1 = new Plane(1,0,0,100, 1, runway, atc);
		Plane plane2 = new Plane(1,0,0,100, 2, runway, atc);
		Plane plane3 = new Plane(1,0,0,100, 3, runway, atc);
		Plane plane4 = new Plane(1,0,0,100, 4, runway, atc);
		Plane plane5 = new Plane(1,0,0,100, 5, runway, atc);
		Plane plane6 = new Plane(1,0,0,100, 6, runway, atc);
		Plane plane7 = new Plane(1,0,0,100, 7, runway, atc);
		//create planes that use different runways
		Plane plane8 = new Plane(1,0,0,45, 8, runway1, atc);
		Plane plane9 = new Plane(1,0,0,45, 9, runway2, atc);
		//create a 1 man maintenance crew for each plane
		plane1.addPlanePersonnel(new PlanePersonnel("Frank", 4, "Plane Refueler", 0, plane1));
		plane2.addPlanePersonnel(new PlanePersonnel("Fran", 5, "Plane Refueler", 0 , plane2));
		plane3.addPlanePersonnel(new PlanePersonnel("Fred", 6, "Plane Refueler", 0 , plane3));
		plane4.addPlanePersonnel(new PlanePersonnel("Phil", 7, "Plane Refueler", 0 , plane4));
		plane5.addPlanePersonnel(new PlanePersonnel("Farid", 7, "Plane Refueler", 0 , plane5));
		plane6.addPlanePersonnel(new PlanePersonnel("Fannie", 8, "Plane Refueler", 0 , plane6));
		plane7.addPlanePersonnel(new PlanePersonnel("Felicia", 9, "Plane Refueler", 0 , plane7));
		plane8.addPlanePersonnel(new PlanePersonnel("Fabian",208, "Plane Refueler", 0 , plane8));
		plane9.addPlanePersonnel(new PlanePersonnel("Don", 209, "Plane Refueler", 0 , plane9));
		//add personnel to the runway
		runway.addRunwayPersonnel(rwp1);
		runway.addRunwayPersonnel(rwp2);
		runway.addRunwayPersonnel(rwp3);
		//in the emergency state, no planes can take off or land from any runway
		atc.emergencyActivated();
		try {
			Thread.sleep(5000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//once deactivated, the planes can take off
		atc.emergencyDeactivated();
		//same function as 
		atc.foundHazard(runway);
	}
}

