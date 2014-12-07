% velocities - desired EE velocities in {BF} as a vector containing 3 numbers each
% returns: joint velocities
function out = p3D2J(v_velocities, w_velocities)
    % initialization
    Q = [0,0,0]

    L1 = Link([Q(1) -15 0 0],'standard')
    L2 = Link([Q(2) 0 0 -pi/2],'standard')
    L3 = Link([0 0 20 0],'standard')
    
    robot = SerialLink([L1 L2 L3], 'name', 'robot'); 
    
    jac = robot.jacob0(zeros(1,3))
    pseudo_inverse_j = pinv(jac)
    
    out = transpose(pseudo_inverse_j * transpose([v_velocities, w_velocities]))
    
    for i = 0:1:100 
        robot.plot(out * i / 10)
    end
end
