classdef Bot
    properties
        handle
        leftMotor
        rightMotor
        touch
        gyro
        sonic
        sonicMotor
        period
        wheelRadius
    end

    methods

        function obj = Bot()
            obj.handle = legoev3('usb');
            obj.leftMotor = motor(obj.handle, 'D');
            obj.rightMotor = motor(obj.handle, 'A');
            obj.touch = touchSensor(obj.handle, 1);
            obj.gyro = gyroSensor(obj.handle, 4);
            obj.sonic = sonicSensor(obj.handle, 3);
            obj.sonicMotor = motor(obj.handle, 'C');
            obj.period = 0.100;
            obj.wheelRadius = 28;
        end

        function stopMotors(obj)
            stop(obj.leftMotor)
            stop(obj.rightMotor)
        end

        function wait(obj)
            pause(obj.period)
        end

        function startMotors(obj)
            start(obj.leftMotor)
            start(obj.rightMotor)
        end

        function resetRotations(obj)
            resetRotation(obj.leftMotor);
            resetRotation(obj.rightMotor);
        end

        function clearSpeed(obj)
            obj.leftMotor.Speed = 0;
            obj.rightMotor.Speed = 0;
        end

        function rotate(obj, angle)
            obj.clearSpeed()
            obj.startMotors();

            resetRotationAngle(obj.gyro);
            currentAngle = 0;
            C = 1;

            while (abs(currentAngle - angle) > 1) && (readTouch(obj.touch) ~= 1)
                currentAngle = readRotationAngle(obj.gyro)
                angleError = angle - currentAngle;

                speed = max(abs(int8(angleError * C)), 15);

                obj.leftMotor.Speed = int8(sign(angleError)) * speed;
                obj.rightMotor.Speed = -int8(sign(angleError)) * speed;

                pause(obj.period);
            end

            obj.clearSpeed();
            obj.stopMotors();
        end

        function goStraight(obj, distance, speed)
            Kp = 0.1;
            Ki = 0.01;
            Kd = 0.01;
            Ca = 2;

            obj.leftMotor.Speed = 0;
            obj.rightMotor.Speed = 0;

            obj.resetRotations();
            obj.startMotors();

            initialAngle = readRotationAngle(obj.gyro);

            traveledDistance = 0;
            lastLeftRotation = 0;
            lastRightRotation = 0;
            leftIntegral = 0;
            rightIntegral = 0;
            lastLeftSpeedError = 0;
            lastRightSpeedError = 0;

            while (traveledDistance <= distance) && (readTouch(obj.touch) ~= 1)
                leftRotation = double(readRotation(obj.leftMotor));
                rightRotation = double(readRotation(obj.rightMotor));

                % Linear velocity, in mm/sec.
                leftSpeed = deg2rad(leftRotation - lastLeftRotation) * ...
                    obj.wheelRadius / obj.period;
                rightSpeed = deg2rad(rightRotation - lastRightRotation) * ...
                    obj.wheelRadius / obj.period;

                currentAngle = readRotationAngle(obj.gyro);
                % angleError > 0 for left tilt, < 0 for right tilt.
                angleError = initialAngle - currentAngle

                leftSpeedError = (speed - leftSpeed) + Ca * angleError;
                rightSpeedError = (speed - rightSpeed) - Ca * angleError;

                leftIntegral = leftIntegral + leftSpeedError;
                rightIntegral = rightIntegral + rightSpeedError;

                leftDerivative = leftSpeedError - lastLeftSpeedError;
                rightDerivative = rightSpeedError - lastRightSpeedError;

                leftCorrection = int8(Kp * leftSpeedError + ...
                        Ki * leftIntegral + ...
                        Kd * leftDerivative);
                rightCorrection = int8(Kp * rightSpeedError + ...
                    Ki * rightIntegral + ...
                    Kd * rightDerivative);

                newLeftSpeed = obj.leftMotor.Speed + leftCorrection;
                newRightSpeed = obj.rightMotor.Speed + rightCorrection;

                obj.leftMotor.Speed = newLeftSpeed;
                obj.rightMotor.Speed = newRightSpeed;

                lastLeftRotation = leftRotation;
                lastRightRotation = rightRotation;

                lastLeftSpeedError = leftSpeedError;
                lastRightSpeedError = rightSpeedError;

                averageSpeed = (leftSpeed + rightSpeed) / 2

                traveledDistance = traveledDistance + abs(averageSpeed) * obj.period

                obj.wait();
            end

            obj.clearSpeed();
            obj.stopMotors();
        end

        function goCircle(obj, radius)
            Kp = 0.1;
            Ki = 0.01;
            Kd = 0.01;

            d = 160
            left_speed = 15
            right_speed = (r - d/2) / (r + d/2) * left_speed

            obj.leftMotor.Speed = 0;
            obj.rightMotor.Speed = 0;

            obj.resetRotations();
            obj.startMotors();

            lastLeftRotation = 0;
            lastRightRotation = 0;
            leftIntegral = 0;
            rightIntegral = 0;
            lastLeftSpeedError = 0;
            lastRightSpeedError = 0;

            while abs(readRotationAngle(obj.gyro)) - 360 > 1
                leftRotation = double(readRotation(obj.leftMotor));
                rightRotation = double(readRotation(obj.rightMotor));

                % Linear velocity, in mm/sec.
                leftSpeed = deg2rad(leftRotation - lastLeftRotation) * ...
                    obj.wheelRadius / obj.period;
                rightSpeed = deg2rad(rightRotation - lastRightRotation) * ...
                    obj.wheelRadius / obj.period;

                leftSpeedError = speed - leftSpeed;
                rightSpeedError = speed - rightSpeed;

                leftIntegral = leftIntegral + leftSpeedError;
                rightIntegral = rightIntegral + rightSpeedError;

                leftDerivative = leftSpeedError - lastLeftSpeedError;
                rightDerivative = rightSpeedError - lastRightSpeedError;

                leftCorrection = int8(Kp * leftSpeedError + ...
                        Ki * leftIntegral + ...
                        Kd * leftDerivative);
                rightCorrection = int8(Kp * rightSpeedError + ...
                    Ki * rightIntegral + ...
                    Kd * rightDerivative);

                newLeftSpeed = obj.leftMotor.Speed + leftCorrection;
                newRightSpeed = obj.rightMotor.Speed + rightCorrection;

                obj.leftMotor.Speed = newLeftSpeed;
                obj.rightMotor.Speed = newRightSpeed;

                lastLeftRotation = leftRotation;
                lastRightRotation = rightRotation;

                lastLeftSpeedError = leftSpeedError;
                lastRightSpeedError = rightSpeedError;

                obj.wait();
            end

            obj.clearSpeed();
            obj.stopMotors();
        end
    end
end
