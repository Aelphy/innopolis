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
        width
        length
        sonicCenterFromFront
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
            obj.width = 0.18;
            obj.length = 0.3;
            obj.sonicCenterFromFront = 0;
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

        function goCircle(obj, radius)
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
        
        function setHeadPosition(obj, angle)
            obj.sonicMotor.Speed = 0;
 
            speed = 25;
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
        
        function [minAngle, minDistance] = findClosestWall(obj)
            speed = 25;
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
            
            obj.setHeadPosition(minAngle)
        end
        
        function goToWall(obj, minDistance, maxDistance)
            speed = 200;

            for i=1:3
                [minAngle, distance] = findClosestWall(obj);
                obj.rotate(minAngle);
                obj.setHeadPosition(0);
            end
            
            d = distance + obj.sonicCenterFromFront;
            
            while d < minDistance || d > maxDistance
                if d < minDistance
                    obj.goStraight((maxDistance - minDistance) / 2 - d, -speed);
                else
                    obj.goStraight(d - (maxDistance - minDistance) / 2, speed);
                end
                
                d = readDistance(obj.sonic) + obj.sonicCenterFromFront;
            end
            
            obj.rotate(90);
            obj.setHeadPosition(-90);
        end
        
        function color = readColor(obj)
            color = readColor(obj.color)
        end
        
        function d = getWallDistance(obj)
            d = readDistance(obj.sonic) - obj.width / 2;
            while (d > 2.5 - obj.sonicCenterFromFront)
                d = readDistance(obj.sonic) - obj.width / 2;
            end
        end
        
        function [traveledDistance] = followWall(obj, desiredDistance)
            Kp = 0.1;
            Ki = 0.01;
            Kd = 0.01;
            Ca = 10;
            
            hack = 0;
 
            obj.leftMotor.Speed = 0;
            obj.rightMotor.Speed = 0;
 
            obj.resetRotations();
            obj.startMotors();
 
            resetRotationAngle(obj.gyro);
            initialAngle = readRotationAngle(obj.gyro);
            speed = 200;
            traveledDistance = 0;
            lastLeftRotation = 0;
            lastRightRotation = 0;
            leftIntegral = 0;
            rightIntegral = 0;
            lastLeftSpeedError = 0;
            lastRightSpeedError = 0;
            lastTravelDistance = 0;
            
            look_distance = 0;
 
            while ~strcmp(obj.readColor(), 'black') && (readTouch(obj.touch) ~= 1)
                leftRotation = double(readRotation(obj.leftMotor));
                rightRotation = double(readRotation(obj.rightMotor));
 
                % Linear velocity, in mm/sec.
                leftSpeed = deg2rad(leftRotation - lastLeftRotation) * ...
                    obj.wheelRadius / obj.period;
                rightSpeed = deg2rad(rightRotation - lastRightRotation) * ...
                    obj.wheelRadius / obj.period;
                               
                % compute correction
                currentDistance = getWallDistance(obj)
                if (lastTravelDistance ~= 0)
                    sinval = (desiredDistance - currentDistance) / lastTravelDistance;
                    if (sinval > 1)
                        sinval = 1;
                    end
                    if (sinval < -1)
                        sinval = -1;
                    end
 
                    correction = double(toDegrees('radians', asin(sinval)));
                else
                    correction = 0;
                end
                %TODO: check if anomaly exists
               
                % correct initial angle
                initialAngle = initialAngle + correction;
                
                currentAngle = readRotationAngle(obj.gyro);
 
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
                
                lastTravelDistance = abs(averageSpeed) * obj.period;
 
                traveledDistance = traveledDistance + lastTravelDistance;
                
                look_distance = look_distance + lastTravelDistance
                
                obj.wait();
                
                if look_distance > 1000 && hack == 0
                    look_distance = 0
                    
                    obj.stopMotors();
                    obj.setHeadPosition(0);
                    d = readDistance(obj.sonic)
                    
                    if d < 1
                        hack = 1;
                        obj.goStraight((d - desiredDistance) * 100, 300)
                        
                        obj.rotate(90);
                        obj.setHeadPosition(-90);
                        obj.goStraight(300, 300);
                        obj.rotate(-90);
                        obj.goStraight(610, 300);
                        obj.rotate(-90);
                        obj.goStraight(250, 300);
                        obj.rotate(90);
                    end
                    
                    obj.setHeadPosition(-90);
                    obj.followWall(desiredDistance);
                    break;
                end
            end
            
            obj.stopMotors()
        end
    end
end
