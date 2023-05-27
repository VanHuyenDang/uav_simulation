#include<iostream>
#include <fstream>
#include <sstream>

#define TIME_STEP 0.01
#define UAV_MASS 5.0
#define MIN_GROUND_CLEARANCE 0.5
#define MIN_BATTERY_LEVEL 40.0



class UAV{
private:
    /*
        Let's say UAV owns some properties:
            - UAV's name
            - UAV's latitude
            - UAV's longitude
            - UAV's altitude
            - UAV's battery level
    */
    std::string name;
    float latitude;
    float longitude;
    float altitude;
    float speed;
    float batteryLevel;
public:
    UAV(const std::string& uavName) : name(uavName) {
        // Initialize other properties
        latitude = 0.0;
        longitude = 0.0;
        altitude = 0.8;
        speed = 0.0;
        batteryLevel = 100.0;
    }
    /*
        Assume the UAV has some movement features, which can be accompanied by
        member functions like:
            - take-off 
            - land
            - fly to
            - change altitude
            - monitor battery level
    */
   void takeOff(float thrust, float takeoffTime){
        /*
            The UAV will take off when some conditions are satisfied only:
                - pre-flight check
                - ground-clearance check
                - battery level check
                - ...
        */
        // TODO: Perform pre-flight checks and condition checks

        if (altitude < MIN_GROUND_CLEARANCE) {
            std::cout << "Takeoff failed due to insufficient ground clearance.\n";
            return;
        }

        if (batteryLevel < MIN_BATTERY_LEVEL) {
            std::cout << "Takeoff failed due to low battery level.\n";
            return;
        }
        // TODO: check if it has GPS lock
        // TODO: check the flight mode
        // TODO: check the weather condition
        // TODO: check permission

        // If all conditions pass, proceed with takeoff
        std::cout << "Taking off...\n";

        // Simulate the UAV's takeoff dynamics
        /*
            It is more realiable if we consider the altitude dynamics of UAV:
                - Kinematic equation: h = v*t + (1/2)a*t^2
                - Notes:
                        h is the altitude,
                        v is the initial velocity (assumed to be 0 for takeoff),
                        t is the time, and
                        a is the acceleration (thrust / mass).
        */
        // Increase altitude over time until takeoff is complete
        const float acceleration = thrust / UAV_MASS; // Assuming mass of the UAV is known
        for (float time = 0.0; time <= takeoffTime; time += TIME_STEP) {
            altitude += (acceleration * time * time) / 2.0;
            std::cout << "Increasing altitude: " << altitude << " meters.\n";
            // TODO: Update any necessary flight parameters here
        }
        // Print the final altitude
        std::cout << "Takeoff complete. Altitude: " << altitude << " meters.\n";
   }

   void land(){
        // Check if the UAV is already on the ground
        if (altitude == 0) {
            std::cout << "The UAV is already on the ground.\n";
            return; // exist if the condition is not satisfied
        }
        // Perform landing procedure
        std::cout << "Initiating landing procedure...\n";
        // Simulate the UAV's landing dynamics
        const double descentRate = 5.0; // Example descent rate in meters per second
        while (altitude > 0) {
            altitude -= descentRate * TIME_STEP;
            // Update any necessary flight parameters here
        }
        // Ensure the altitude is set to zero to avoid any precision issues
        altitude = 0;
        std::cout << "Landing complete. The UAV is on the ground.\n";
   }

// TODO:    void flyTo()
// TODO:    void changeAltitude()
// TODO:    void displayBatteryLevel()
};

int main() {
    // Define the parameter
    const float thrust = 1000.0; // Example thrust value in Newtons
    const float takeoffTime = 5.0; // Example takeoff time in seconds
    // Declare the first UAV with name MyUAV
    UAV uav("MyUAV");
    uav.takeOff(thrust, takeoffTime);

     // Create a gnuplot object
    Gnuplot plot;

    // Create some data for the UAV's movement
    std::vector<double> xValues = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> yValues = {0.0, 1.0, 0.5, 1.5, 2.0};

    // Set up the plot properties
    plot.set_title("UAV Movement");
    plot.set_xlabel("X");
    plot.set_ylabel("Y");

    // Plot the data
    plot.plot_xy(xValues, yValues, "UAV Path");

    // Wait for a key press to close the plot window
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore();

    return 0;
}