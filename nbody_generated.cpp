#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>

const double G = 4 * M_PI * M_PI;

struct Body {
    double x, y, z;
    double vx, vy, vz;
    double mass;

    Body(double x, double y, double z, double vx, double vy, double vz, double mass)
        : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), mass(mass) {}
};

void apply_offset(std::vector<Body>& bodies) {
    double cm_x = 0.0, cm_y = 0.0, cm_z = 0.0, cm_mass = 0.0;

    for (const auto& body : bodies) {
        cm_x += body.mass * body.x;
        cm_y += body.mass * body.y;
        cm_z += body.mass * body.z;
        cm_mass += body.mass;
    }

    cm_x /= cm_mass;
    cm_y /= cm_mass;
    cm_z /= cm_mass;

    for (auto& body : bodies) {
        body.x -= cm_x;
        body.y -= cm_y;
        body.z -= cm_z;
    }
}

double calculate_energy(const std::vector<Body>& bodies) {
    double kinetic_energy = 0.0;
    double potential_energy = 0.0;

    for (const auto& body : bodies) {
        kinetic_energy += 0.5 * body.mass * (body.vx * body.vx + body.vy * body.vy + body.vz * body.vz);

        for (const auto& other : bodies) {
            if (&body != &other) {
                double dx = body.x - other.x;
                double dy = body.y - other.y;
                double dz = body.z - other.z;
                double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
                potential_energy -= G * body.mass * other.mass / distance;
            }
        }
    }

    return kinetic_energy + potential_energy / 2.0;
}

void update_positions_and_velocities(std::vector<Body>& bodies, double dt) {
    for (auto& body : bodies) {
        for (auto& other : bodies) {
            if (&body != &other) {
                double dx = other.x - body.x;
                double dy = other.y - body.y;
                double dz = other.z - body.z;
                double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
                double force = G * body.mass * other.mass / (distance * distance * distance);

                body.vx += force * dx * dt / body.mass;
                body.vy += force * dy * dt / body.mass;
                body.vz += force * dz * dt / body.mass;
            }
        }
    }

    for (auto& body : bodies) {
        body.x += body.vx * dt;
        body.y += body.vy * dt;
        body.z += body.vz * dt;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [iterations]" << std::endl;
        return 1;
    }

    int iterations = std::atoi(argv[1]);

    std::vector<Body> bodies = {
        // x, y, z, vx, vy, vz, mass (in astronomical units and solar masses)
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0}, // Sun
        {4.84143144246472090e+00, -1.16032004402742839e+00, -1.03622044471123109e-01, 1.66007664274403694e-03 * 365.25, 7.69901118419740425e-03 * 365.25, -6.90460016972063023e-05 * 365.25, 9.54791938424326609e-04}, // Jupiter 
	{8.34336671824457987e+00, 4.12479856412430479e+00, -4.03523417114321381e-01, -2.76742510726862411e-03  * 365.25, 4.99852801234917238e-03 * 365.25, 2.30417297573763929e-05 * 365.25, 2.85885980666130812e-04}, // Saturn
        {1.28943695621391310e+01, -1.51111514016986312e+01, -2.23307578892655734e-01, 2.96460137564761618e-03 * 365.25, 2.37847173959480950e-03 * 365.25, -2.96589568540237556e-05 * 365.25, 4.36624404335156298e-05}, // Uranus
        {1.53796971148509165e+01, -2.59193146099879641e+01, 1.79258772950371181e-01, 2.68067772490389322e-03 * 365.25, 1.62824170038242295e-03 * 365.25, -9.51592254519715870e-05 * 365.25, 5.15138902046611451e-05} // Neptune
    };
//        {5.20336301, 0.0, 0.0, 0.0, 2.96455026048, 0.0, 0.000954791915211}, // Jupiter
//        {9.53707032, 0.0, 0.0, 0.0, 2.16969870115, 0.0, 0.000285885672527}, // Saturn
//        {19.19126393, 0.0, 0.0, 0.0, 1.83254311875, 0.0, 0.000043662440177}, // Uranus
//        {30.06896348, 0.0, 0.0, 0.0, 1.61278484486, 0.0, 0.000051513890469}  // Neptune

    apply_offset(bodies);

    double initial_energy = calculate_energy(bodies);
    std::cout << std::fixed << std::setprecision(12) << "Initial energy: " << initial_energy << std::endl;

    double dt = 0.01;
    for (int i = 0; i < iterations; ++i) {
        update_positions_and_velocities(bodies, dt);
    }

    double final_energy = calculate_energy(bodies);
    std::cout << std::fixed << std::setprecision(12) << "Final energy: " << final_energy << std::endl;

    return 0;
}
