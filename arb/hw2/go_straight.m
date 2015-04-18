function go_straight(robot, left_motor, right_motor, distance, power, step, touch)
    WHEEL_RADIUS = 28;
    Kp=1;
    Ki=1;
    Kd=1;
    Tf=0.5;
    
    controller = pid(Kp, Ki, Kd, Tf);

    robot.outputClrCount(0, left_motor);
    robot.outputClrCount(0, right_motor);
    
    robot.outputPower(0, left_motor, power);
    robot.outputPower(0, right_motor, power);

    traveled_distance = 0;
    last_left_rotation = 0;
    last_right_rotation = 0;

    while (traveled_distance <= distance) && robot.inputReadSI(0, touch, Device.Pushed) ~= 1)
        left_rotation = robot.outputGetCount(0, left_motor);
        right_rotation = robot.outputGetCount(0, right_motor);

        left_speed = (left_rotation - last_left_rotation) / step;
        right_speed = (right_rotation - last_right_rotation) / step;

%         leftMotor.Speed = speed - int8(P * (leftSpeed - rightSpeed));
%         rightMotor.Speed = speed - int8(P * (rightSpeed - leftSpeed));
%
%         speedDiff = abs(leftSpeed - rightSpeed);

%         x = speed + int8(P * (speed - leftSpeed - (leftSpeed - rightSpeed)))
%         y = speed + int8(P * (speed - rightSpeed - (rightSpeed - leftSpeed)))

        left_speed_w_correction =;
        right_speed_w_correction =;
        
        robot.outputPower(0, left_motor, left_speed_w_correction);
        robot.outputPower(0, right_motor, right_speed_w_correction);

        last_left_rotation = leftotation;
        last_right_rotation = right_rotation;

        average_rotation = (left_rotation + right_rotation) / 2;
        traveled_distance = (average_rotation / 360) * (2 * WHEEL_RADIUS);

        pause(step);
    end
end
