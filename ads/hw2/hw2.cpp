#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "hw2.h"
#include "error.h"

#define TRAFFIC_LIGHT_RED 0
#define TRAFFIC_LIGHT_GREEN 1

#define INPUTS_NUMBER 6

void simulate(double arrival, double departure, double runtime, double increment, double red, double green, FILE *fw) {
    double avr_queue_length = 0;
    double avr_waiting_time = 0;
    double max_waiting_time = 0;
    double current_time = 0;
    int tic_counter = 0;
    int traffic_light_counter = 0;
    int departure_counter = 0;
    int max_queue_length = 0;
    int i, j, border, length_buffer;
    int total_cars_number = 0;
    int current_state = TRAFFIC_LIGHT_RED;
    Queue* q = new Queue;
    Node* n;

    // all the runtime
    /* it is finished when number of tics multiplied by increment per tic in seconds
       become bigger than runtime in seconds */
    while((current_time = tic_counter * increment / 1000) < runtime * 60) {
        // compute current traffic light state
        if (current_state == TRAFFIC_LIGHT_GREEN) {
            // checks the need to toogle the light
            // it was tested by outputing the number of toogling per simulation
            if (traffic_light_counter * increment / 1000 < green) {
                traffic_light_counter++;
            } else {
                traffic_light_counter = 0;

                if (red != 0) {
                    current_state = TRAFFIC_LIGHT_RED;
                    //printf("RED %lf\n", current_time);
                }
            }
        } else {
            if (traffic_light_counter * increment / 1000 < red) {
                traffic_light_counter++;
            } else {
                traffic_light_counter = 0;
                // before red light changes to green first car is not ready to leave
                departure_counter = 0;

                if(green != 0) {
                    current_state = TRAFFIC_LIGHT_GREEN;
                    //printf("GREEN %lf\n", current_time);
                }
            }
        }

        // random variable that gives us number of cars per tic
        border = poison_distributed_events_number(arrival * increment / 60000);

        total_cars_number += border;

        // all the cars incoming per tic
        for(i = 0; i < border; ++i) {
            //printf("Car arrived: %lf.\n", current_time);

            if (q->length() == 0 && current_state == TRAFFIC_LIGHT_GREEN) {
                //printf("Car destroyed: %lf.\n", current_time);
                departure_counter = 0;
            } else {
                q->enqueue(new Node(current_time));
            }
        }

        // cars outcoming per tic
        if (current_state == TRAFFIC_LIGHT_GREEN) {
            // if daprture time passed and queue is not empty
            if (departure_counter * increment / 1000 > departure && q->length() > 0) {
                if (departure != 0) {
                    // more than one car can leave the crossroad
                    for (j = 0; j < (increment / (departure * 1000)); ++j) {
                        // if queue is not empty
                        if (q->length() > 0) {
                            departure_counter = 0;

                            // variable to handle poped value
                            Node *car;

                            //printf("Car destroyed: %lf.\n", current_time);
                            car = q->dequeue();

                            // checking was waiting time reached maximum
                            if (max_waiting_time < current_time - car->get_arrival_time()) {
                                max_waiting_time = current_time - car->get_arrival_time();
                            }

                            avr_waiting_time += current_time - car->get_arrival_time();

                            delete car;
                        }
                    }
                } else {
                    while (q->length() > 0) {
                        departure_counter = 0;

                        // variable to handle poped value
                        Node *car;

                        //printf("Car destroyed: %lf.\n", current_time);
                        car = q->dequeue();

                        // checking was waiting time reached maximum
                        if (max_waiting_time < current_time - car->get_arrival_time()) {
                            max_waiting_time = current_time - car->get_arrival_time();
                        }

                        avr_waiting_time += current_time - car->get_arrival_time();

                        delete car;
                    }
                }
            }
        }

        // temp variable for the reason not to recount the length of the queue 3 times
        length_buffer = q->length();

        // check max_length of th queue
        if (max_queue_length < length_buffer) {
            max_queue_length = length_buffer;
        }

        avr_queue_length += length_buffer;

        tic_counter++;
        departure_counter++;
    }

    avr_queue_length = avr_queue_length / tic_counter;

    if (q->length() > 0) {
        n = q->get_first_node();

        while (n != NULL) {
            avr_waiting_time += current_time - n->get_arrival_time();

            // checking was waiting time reached maximum
            if (max_waiting_time < current_time - n->get_arrival_time()) {
                max_waiting_time = current_time - n->get_arrival_time();
            }

            n = n->get_next_node();
        }
    }

    avr_waiting_time = avr_waiting_time / total_cars_number;

    //printf("%d - %d", q->length(), total_cars_number);

    // output the simulation results
    fprintf(fw, "Average length:    %.0lf cars\n", avr_queue_length);
    fprintf(fw, "Maximum length:    %d cars\n", max_queue_length);
    fprintf(fw, "Average wait:      %.0lf seconds\n", avr_waiting_time);
    fprintf(fw, "Maximum wait:      %.0lf seconds\n", max_waiting_time);

    q->empty();

    delete q;
}

char* downcase(const char *str) {
    int i;
    char *str2 = (char*)malloc(31 * sizeof(char));

    strcpy(str2, str);

    for(i = 0; str2[i]; i++) { str2[i] = tolower(str2[i]); }

    return str2;
}

int main() {
    // Seed the random-number generator with current time so that the numbers will be different every time we run
    srand((unsigned) time(NULL));
    int N = 0;
    int i = 0, j = 0;
    double arrival = -1, departure = -1, runtime = -1, increment = -1, red = -1, green = -1, buffer;
    char param_name[250];
    int string_length;
    FILE *fr, *fw;

    if ((fr = fopen("input.txt", "r")) == NULL) {
        error("cannot open the input file.\n");
    }

    if ((fw = fopen("output.txt", "w")) == NULL) {
        error("cannot open the output file.\n");
    }

    // assign N
    // if there is no N in input file then exit with error code
    if (fscanf(fr, "%d", &N) != 1) {
        error("Cannot read N.\n");
    }

    // check N
    // check that N has valid value
    if (!(N > 0 && N < 1000)) {
        printf("N is wrong.\n");
        exit(1);
    }

    fprintf(fw, "Usvyatsov Mikhail\n");

    // for each input test parse simulation parameters and run simulation
    for(i = 0; i < N; ++i) {
        // parsing simulation parameters
        for(j = 0; j < INPUTS_NUMBER; ++j) {
            if (fscanf(fr, "%s %lf", param_name, &buffer) != 2) {
                error("cannot read parameter.\n");
            }

            // assign parameter to its variable

            if (strncmp(downcase(param_name), "arrival", strlen("arrival")) == 0) {
                arrival = buffer;
                continue;
            }

            if (strncmp(downcase(param_name), "departure", strlen("departure")) == 0) {
                departure = buffer;
                continue;
            }

            if (strncmp(downcase(param_name), "runtime", strlen("runtime")) == 0) {
                runtime = buffer;
                continue;
            }

            if (strncmp(downcase(param_name), "increment", strlen("increment")) == 0) {
                increment = buffer;
                continue;
            }

            if (strncmp(downcase(param_name), "red", strlen("red")) == 0) {
                red = buffer;
                continue;
            }

            if (strncmp(downcase(param_name), "green", strlen("green")) == 0) {
                green = buffer;
                continue;
            }
        }

        // check availability simulation parameters
        if (arrival == -1) {
            error("arrival was not set.\n");
        }

        if (departure == -1) {
            error("departure is not set.\n");
        }

        if (runtime == -1) {
            error("runtime is not set.\n");
        }

        if (increment == -1) {
            error("increment is not set.\n");
        }

        if (red == -1) {
            error("red is not set.\n");
        }

        if (green == -1) {
            error("green is not set.\n");
        }

        // output parameters of current simulation
        fprintf(fw, "Arrival rate:      %.0lf cars per minute\n", arrival);
        fprintf(fw, "Departure:         %.0lf seconds per car\n", departure);
        fprintf(fw, "Runtime:           %.0lf minutes\n", runtime);
        fprintf(fw, "Time increment:    %.0lf milliseconds\n", increment);
        fprintf(fw, "Light squence:     Red %.0lf seconds, Green %.0lf seconds\n", red, green);

        // start simulation
        simulate(arrival, departure, runtime, increment, red, green, fw);

        fprintf(fw, "\n");

        arrival = departure = runtime = increment = red = green = -1;
    }

    fclose(fr);
    fclose(fw);

    return 0;
}
