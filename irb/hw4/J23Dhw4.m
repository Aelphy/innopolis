% velocities - vector of desired joint velocities matrix of EE
% output - EE velocities wrt baseframe
function out = J23D(velocities)
    % initialization
    Q = [0,0,0]

    L1 = Link([Q(1) -15 0 0],'standard')
    L2 = Link([Q(2) 0 0 -pi/2],'standard')
    L3 = Link([0 0 20 0],'standard')
    
    robot = SerialLink([L1 L2 L3], 'name', 'robot'); 
    
    out = robot.jacob0(zeros(1,3)) * transpose([velocities,0])
    
    for i = 0:1:100
        robot.plot([velocities * i / 10, 0])
    end
end
