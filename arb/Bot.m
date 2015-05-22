classdef Bot
    properties
        handle
        leftMotor
        rightMotor
        touch
        gyro
        color
        sonic
        sonicMotor
        period
        wheelRadius
        sonicPosition
    end

    methods

        function obj = Bot()
            obj.handle = legoev3('usb');
            obj.leftMotor = motor(obj.handle, 'D');
            obj.rightMotor = motor(obj.handle, 'A');
            obj.touch = touchSensor(obj.handle, 4);
            obj.gyro = gyroSensor(obj.handle, 1);
            obj.sonic = sonicSensor(obj.handle, 3);
            obj.sonicMotor = motor(obj.handle, 'B');
            obj.color = colorSensor(obj.handle, 2);
            obj.period = 0.100;
            obj.wheelRadius = 28;
            obj.sonicPosition = readRotation(obj.sonicMotor);
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
                angleError = initialAngle - currentAngle;

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

                averageSpeed = (leftSpeed + rightSpeed) / 2;

                traveledDistance = traveledDistance + abs(averageSpeed) * obj.period

                obj.wait();
            end

            obj.clearSpeed();
            obj.stopMotors();
        end

        function go_circle(obj, radius)
            Kp = 0.1;
            Ki = 0.01;
            Kd = 0.01;

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
        
        function set_head_position(obj, angle)
            obj.sonicMotor.Speed = 0;
 
            speed = 15;
            currentAngle = readRotation(obj.sonicMotor) - obj.sonicPosition;
 
            start(obj.sonicMotor);

            while abs(currentAngle - angle) > 1
                currentAngle = readRotation(obj.sonicMotor) - obj.sonicPosition
                angleError = angle - currentAngle;
                obj.sonicMotor.Speed = int8(sign(angleError)) * speed;
                pause(obj.period / 20);
            end

            stop(obj.sonicMotor);
            
            obj.sonicMotor.Speed = 0;
        end
        
        function [minAngle, minDistance] = find_closest_wall(obj)
            speed = 15;
            r = 0;
 
            obj.sonicMotor.Speed = -speed;
            while r > -180
                start(obj.sonicMotor);
                obj.wait();
                stop(obj.sonicMotor);
                r = readRotation(obj.sonicMotor) - obj.sonicPosition;
            end
            
            minDistance = 255;
            minAngle = 0;
            obj.sonicMotor.Speed = speed;

            while r < 180
                start(obj.sonicMotor);
                obj.wait();
                stop(obj.sonicMotor);

                r = readRotation(obj.sonicMotor) - obj.sonicPosition;
                d = readDistance(obj.sonic);

                if d < minDistance
                    minDistance = d;
                    minAngle = r;
                end
            end
            
            obj.set_head_position(minAngle)
        end
        
        function go_to_wall(obj, distance)
            speed = 100;

            for i=1:3
                [minAngle, minDistance] = find_closest_wall(obj);
                obj.rotate(minAngle);
                obj.set_head_position(0);
            end
            
            d = minDistance
            
            while d >= distance
                obj.goStraight(d - distance, speed);
                d = readDistance(obj.sonic)
            end
            
            obj.rotate(90);
            obj.set_head_position(-90);
        end
    end
end
