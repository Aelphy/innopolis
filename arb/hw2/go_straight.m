function go_straight(leftMotor, rightMotor, distance, speed, step, touch)

    P = 0.01;

    WHEEL_RADIUS = 28;

    resetRotation(leftMotor);
    resetRotation(rightMotor);

    leftMotor.Speed = speed;
    rightMotor.Speed = speed;

    traveledDistance = 0;
    lastLeftRotation = 0;
    lastRightRotation = 0;

    while (traveledDistance <= distance) && (readTouch(touch) ~= 1)
        leftRotation = readRotation(leftMotor);
        rightRotation = readRotation(rightMotor);

        leftSpeed = (leftRotation - lastLeftRotation) / step;
        rightSpeed = (rightRotation - lastRightRotation) / step;

%         leftMotor.Speed = speed - int8(P * (leftSpeed - rightSpeed));
%         rightMotor.Speed = speed - int8(P * (rightSpeed - leftSpeed));
%
%         speedDiff = abs(leftSpeed - rightSpeed);

%         x = speed + int8(P * (speed - leftSpeed - (leftSpeed - rightSpeed)))
%         y = speed + int8(P * (speed - rightSpeed - (rightSpeed - leftSpeed)))

        leftMotor.Speed = x;
        rightMotor.Speed = y;

        lastLeftRotation = leftRotation;
        lastRightRotation = rightRotation;

        averageRotation = (leftRotation + rightRotation) / 2;
        traveledDistance = (averageRotation/360) * (2*WHEEL_RADIUS);

        pause(step);
    end
end
