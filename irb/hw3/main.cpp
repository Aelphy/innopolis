#include <yarp/os/all.h>
#include <string.h>
#include <math.h>

using namespace std;
using namespace yarp::os;

vector < vector <double> > find_transform_matrix(double in1, double in2, double in3, double in4, double in5, double in6) {
    vector < vector <double> > matrix = {{}, {}, {}, {}};

    double theta[6] = {in1 * M_PI / 180, in2 * M_PI / 180, in3 * M_PI / 180, in4 * M_PI / 180, in5 * M_PI / 180, in6 * M_PI / 180};

    matrix[0].push_back(-cos(theta[5]) * sin(theta[0]) * sin(theta[3] + theta[4]) + cos(theta[0]) * (cos(theta[1] + theta[2]) * cos(theta[3] + theta[4]) * cos(theta[5]) - sin(theta[1] + theta[2]) * sin(theta[5])));
    matrix[0].push_back(sin(theta[0]) * sin(theta[3] + theta[4]) * sin(theta[5]) - cos(theta[0]) * (cos(theta[5]) * sin(theta[1] + theta[2]) + cos(theta[1] + theta[2]) * cos(theta[3] + theta[4]) * sin(theta[5])));
    matrix[0].push_back(cos(theta[3]) * (cos(theta[4]) * sin(theta[0]) + cos(theta[0]) * cos(theta[1] + theta[2]) * sin(theta[4])) + sin(theta[3]) * (cos(theta[0]) * cos(theta[1] + theta[2]) * cos(theta[4]) - sin(theta[0]) * sin(theta[4])));
    matrix[0].push_back((cos(theta[0]) * (20 * cos(theta[1]) - 6 + 15 * cos(theta[1] + theta[2] - theta[3]) + 15 * cos(theta[1] + theta[2] + theta[3]) + 4 * sin(theta[1] + theta[2])) - 30 * sin(theta[0]) * sin(theta[3])) / 20);

    matrix[1].push_back(cos(theta[5]) * (cos(theta[4]) * (cos(theta[1]) * cos(theta[2]) * cos(theta[3]) * sin(theta[0]) - cos(theta[3]) * sin(theta[0]) * sin(theta[1]) * sin(theta[2]) + cos(theta[0]) * sin(theta[3])) + (cos(theta[0]) * cos(theta[3]) - cos(theta[1] + theta[2]) * sin(theta[0]) * sin(theta[3])) * sin(theta[4])) - sin(theta[0]) * sin(theta[1] + theta[2]) * sin(theta[5]));
    matrix[1].push_back(-cos(theta[5]) * sin(theta[0]) * sin(theta[1] + theta[2]) - (cos(theta[4]) * (cos(theta[1]) * cos(theta[2]) * cos(theta[3]) * sin(theta[0]) - cos(theta[3]) * sin(theta[0]) * sin(theta[1]) * sin(theta[2]) + cos(theta[0]) * sin(theta[3])) + (cos(theta[0]) * cos(theta[3]) - cos(theta[1] + theta[2]) * sin(theta[0]) * sin(theta[3])) * sin(theta[4])) * sin(theta[5]));
    matrix[1].push_back(-cos(theta[0]) * cos(theta[3] + theta[4]) + cos(theta[1] + theta[2]) * sin(theta[0]) * sin(theta[3] + theta[4]));
    matrix[1].push_back((sin(theta[0]) * (20 * cos(theta[1]) -6 + 15 * cos(theta[1] + theta[2] - theta[3]) + 15 * cos(theta[1] + theta[2] + theta[3]) + 4 * sin(theta[1] + theta[2])) + 30 * cos(theta[0]) * sin(theta[3])) / 20);

    matrix[2].push_back(-cos(theta[3] + theta[4]) * cos(theta[5]) * sin(theta[1] + theta[2]) - cos(theta[1] + theta[2]) * sin(theta[5]));
    matrix[2].push_back(-cos(theta[1] + theta[2]) * cos(theta[5]) + cos(theta[3] + theta[4]) * sin(theta[1] + theta[2]) * sin(theta[5]));
    matrix[2].push_back(-sin(theta[1] + theta[2]) * sin(theta[3] + theta[4]));
    matrix[2].push_back(cos(theta[1] + theta[2]) / 5 + (- (2 + 3 * cos(theta[2]) * cos(theta[3])) * sin(theta[1]) - 3 * cos(theta[1]) * cos(theta[3]) * sin(theta[2])) / 2);

    matrix[3].push_back(0);
    matrix[3].push_back(0);
    matrix[3].push_back(0);
    matrix[3].push_back(1);

    return matrix;
}

int main(int argc, char *argv[]) {
    int i = 0, j = 0;
    double in[6];
    bool params_are_correct = true;
    vector < vector <double> > transformation_matrix;
    Network n;
    BufferedPort<Bottle> user_commands, user_quit, info, result;

    user_commands.open("/user_commands");
    user_quit.open("/quit");
    info.open("/info");
    result.open("/result");

    n.connect("/UserCommands", user_commands.getName());
    n.connect("/UserQuit", user_quit.getName());
    n.connect(info.getName(), "/Info");
    n.connect(result.getName(), "/ResultR");

    Bottle& output = info.prepare();

    output.clear();
    output.addString("Now you have to input to port “UserCommands” in format <in1 in2 in3 in4 in5 in6>, where each inX is angle thetaX in format “double. Each parameter inX is between -180 and 180 degrees");
    info.write(true);

    while(true) {
        Bottle *user_quit_input = user_quit.read(false);
        Bottle *user_commands_input = user_commands.read(false);

        if (user_quit_input != NULL && strcmp(user_quit_input->toString().c_str(), "quit") == 0) {
            return 0;
        }

        if(user_commands_input != NULL) {
            if(sscanf(user_commands_input->toString().c_str(), "%lf %lf %lf %lf %lf %lf", &in[0], &in[1], &in[2], &in[3], &in[4], &in[5]) == 6) {
                for(i = 0; i < 6; ++i) {
                    if (in[i] < -180 || in[i] > 180) {
                        Bottle& output = info.prepare();

                        output.clear();
                        output.addString("Error: every angle should be between -180 and 180 degrees");
                        info.write(true);
                        params_are_correct = false;
                    }
                }

                if (params_are_correct) {
                    transformation_matrix = find_transform_matrix(in[0], in[1], in[2], in[3], in[5], in[6]);

                    for(i = 0; i < 4; ++i) {
                        Bottle& output = result.prepare();

                        output.clear();

                        for(j = 0; j < 4; ++j) {
                            output.addDouble(transformation_matrix[i][j]);
                        }

                        result.write(true);
                    }
                }

                params_are_correct = true;
            } else {
                Bottle& output = info.prepare();

                output.clear();
                output.addString("Wrong format of input string");
                info.write(true);
            }
        }
    }

    return 0;
}
