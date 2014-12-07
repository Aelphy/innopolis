% angles - 1 * 6 matrix with angles in radians
% returns: Honogenious matrix 4*4
function out = WHERE(angles)
    % robot initialization
    L = [1,1,0.5]
    Q = [0,0,-pi/2,0,0,0]

    L1 = Link([Q(1) 0 0 0],'standard')
    L2 = Link([Q(2)-pi/2 0 0 pi/2],'standard')
    L3 = Link([Q(3)+pi 0 0 -pi/2],'standard')
    L4 = Link([Q(4) 0 L(1) 0],'standard')
    L5 = Link([Q(5)+pi/2 0 L(2) 0],'standard')
    L6 = Link([Q(6) 0 0 -pi/2],'standard')
    L7 = Link([0 0 L(3) 0],'standard')

    robot = SerialLink([L1 L2 L3 L4 L5 L6 L7], 'name', 'robot');
    robot.plot([Q, 0])

    robot.animate([Q + angles, 0])
    % using robotics toolbox built in inverse kinematics method
    out = robot.fkine([angles,0])
end