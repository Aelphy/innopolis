% velocities - desired EE velocities in {BF} as a vector containing 3 numbers each
% returns: joint velocities
function out = p3D2J(v_velocities, w_velocities)
    % initialization
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
    
    jac = robot.jacob0(zeros(1,7))
    pseudo_inverse_j = pinv(jac)
    
    % finding pseudoinverse jacobian allows us to compute inverse velocity
    % problem, the arbitrary vector was taken as zero.
    out = transpose(pseudo_inverse_j * transpose([v_velocities, w_velocities]))
    
    for i = 0:1:100 
        robot.plot(out * i / 10)
    end
end
