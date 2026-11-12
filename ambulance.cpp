#include <iostream>
#include <string>

using namespace std;

class Ambulance {
private:
    string id;
    double distanceToSignal; // in meters
    bool verified;

public:
    Ambulance(string vehicleId, double initialDist) {
        id = vehicleId;
        distanceToSignal = initialDist;
        verified = false;
    }

    string getId() const { return id; }
    double getDistance() const { return distanceToSignal; }
    bool isCaseVerified() const { return verified; }

    void setVerification(bool status) {
        verified = status;
    }

    // Simulate GPS updating the distance as the ambulance moves
    void updateDistance(double newDist) {
        distanceToSignal = newDist;
        cout << "[GPS Update] Ambulance " << id << " is now " << distanceToSignal << " meters away.\n";
    }
};

class StationMaster {
public:
    // Step 1: Station Master checks and verifies the emergency case
    void verifyAmbulanceCase(Ambulance &amb) {
        cout << "\n[Station Master] Reviewing emergency request for Ambulance " << amb.getId() << "...\n";
        amb.setVerification(true);
        cout << "[Station Master] Status: Case Verified Successfully.\n";
    }

    // Step 2: Check GPS distance and trigger the automation button
    void triggerAutomationButton(Ambulance &amb, double thresholdMeters) {
        cout << "\n[System] Checking proximity (Threshold: " << thresholdMeters << "m)...\n";

        if (amb.getDistance() <= thresholdMeters) {
            if (amb.isCaseVerified()) {
                cout << "[TRIGGER BUTTON PRESSED] Station Master activated automation override!\n";
                cout << ">>> TRAFFIC SIGNAL TURNED GREEN. Lane cleared for Ambulance " << amb.getId() << "! <<<\n";
            } else {
                cout << "[BLOCKED] Cannot automate: Emergency case has not been verified yet.\n";
            }
        } else {
            cout << "[STATUS] Ambulance is still too far. Signal remains normal.\n";
        }
    }
};

int main() {
    cout << "=== Simple Automatic Lane Clearance Simulation ===\n\n";

    // Initialize Ambulance 600 meters away from the signal
    Ambulance myAmbulance("AMB-101", 600.0);
    StationMaster master;

    // 1. Station Master verifies the case
    master.verifyAmbulanceCase(myAmbulance);

    // 2. Test when ambulance is still far away (600m - threshold is 500m)
    master.triggerAutomationButton(myAmbulance, 500.0);

    // 3. Ambulance moves closer via GPS tracking (now 350 meters away)
    cout << "\n--- Ambulance moves closer ---\n";
    myAmbulance.updateDistance(350.0);

    // 4. Trigger button again within threshold
    master.triggerAutomationButton(myAmbulance, 500.0);

    return 0;
}