#include <osLayer.hpp>
#include <vector>

// Define a Keybind struct to encapsulate key combination logic
struct Keybind {
    std::vector<int> requiredKeys; // Keys that must be pressed
    int triggerKey;               // The key that triggers the action

    // Check if the keybind is activated
    bool IsActivated(OSLayer &os) const {
        // Ensure all required keys are down
        for (int key : requiredKeys) {
            if (!os.IsKeyDown((char)key)) {
                return false;
            }
        }

        // Ensure the trigger key is pressed
        if (!os.GetKeyPresssed((char)triggerKey)) {
            return false;
        }

        // Ensure no other keys are pressed
        for (int key = 0; key < 256; key++) {
            if (std::find(requiredKeys.begin(), requiredKeys.end(), key) == requiredKeys.end() &&
                key != triggerKey && os.IsKeyDown((char)key)) {
                return false;
            }
        }

        return true;
    }
};