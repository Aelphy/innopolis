#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hw2.h"
#include "error.h"

#define TRAFFIC_LIGHT_RED 0
#define TRAFFIC_LIGHT_GREEN 1

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
       become bigger than runtime in seconds*/
    while((current_time = tic_counter * increment / 1000) < runtime * 60) {
        // compute current traffic light state
        if (current_state == TRAFFIC_LIGHT_GREEN) {
            // checks the need to toogle the light
            // it was tested by outputing the number of toogling per simulation
            if (traffic_light_counter * increment / 1000 < green) {
                traffic_light_counter++;
            } else {
                traffic_light_counter = 0;
                current_state = TRAFFIC_LIGHT_RED;
                //printf("RED %d\n", tic_counter);
            }
        } else {
            if (traffic_light_counter * increment / 1000 < red) {
                traffic_light_counter++;
            } else {
                traffic_light_counter = 0;
                // before red light changes to green first car is not ready to leave
                departure_counter = 0;
                current_state = TRAFFIC_LIGHT_GREEN;
                //printf("GREEN %d\n", tic_counter);
            }
        }

        // random variable that gives us number of cars per tic
        border = poison_distributed_events_number(arrival * increment / 60000);

        total_cars_number += border;

        // all the cars incoming per tic
        for(i = 0; i < border; ++i) {
            //printf("Car arrived: tic - %d.\n", tic_counter);
            q->enqueue(new Node (current_time));
        }

        // cars outcoming per tic
        if (current_state == TRAFFIC_LIGHT_GREEN) {
            // if daprture time passed and queue is not empty
            if (departure_counter * increment / 1000 > departure && q->length() > 0) {
                departure_counter = 0;

                // more than one car can leave the crossroad
                for (j = 0; j < (increment / (departure * 1000) + 1); ++j) {
                    // if queue is not empty
                    if (q->length() > 0) {
                        // variable to handle poped value
                        Node *car;

                        //printf("Car destroyed: tic - %d.\n", tic_counter);
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
    fprintf(fw, "Average length: %.0lf cars\n", avr_queue_length);
    fprintf(fw, "Maximum length: %d cars\n", max_queue_length);
    fprintf(fw, "Average wait: %.0lf seconds\n", avr_waiting_time);
    fprintf(fw, "Maximum wait: %.0lf seconds\n", max_waiting_time);

    q->empty();

    delete q;
}

int main() {
    // Seed the random-number generator with current time so that the numbers will be different every time we run
    srand((unsigned) time(NULL));
    int N = 0;
    int i = 0;
    double arrival, departure, runtime, increment, red, green;
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

    fprintf(fw, "Usvyatsov Mikhail\n\n");

    // for each input test parse simulation parameters and run simulation
    for(i = 0; i < N; ++i) {
        // parsing simulation parameters
        if (fscanf(fr, " Arrival %lf", &arrival) != 1) {
            error("cannot read arrival.\n");
        }

        if (fscanf(fr, " Departure %lf", &departure) != 1) {
            error("cannot read departure.\n");
        }

        if (fscanf(fr, " Runtime %lf", &runtime) != 1) {
            error("cannot read runtime.\n");
        }

        if (fscanf(fr, " Increment %lf", &increment) != 1) {
            error("cannot read increment.\n");
        }

        if (fscanf(fr, " Red %lf", &red) != 1) {
            error("cannot read red.\n");
        }

        if (fscanf(fr, " Green %lf", &green) != 1) {
            error("cannot read green.\n");
        }

        // output parameters of current simulation
        fprintf(fw, "Arrival rate: %.0lf cars per minute\n", arrival);
        fprintf(fw, "Departure: %.0lf seconds per car\n", departure);
        fprintf(fw, "Runtime: %.0lf minutes\n", runtime);
        fprintf(fw, "Time increment: %.0lf milliseconds\n", increment);
        fprintf(fw, "Light squence: Red %.0lf seconds, Green %.0lf seconds\n", red, green);

        // start simulation
        simulate(arrival, departure, runtime, increment, red, green, fw);
    }

    fclose(fr);
    fclose(fw);

    return 0;
}
