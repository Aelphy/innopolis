% ee_matrix - Honogenious matrix of EE
% returns: 1*6 vector of nessesery angles in radians
function out = HOWTO_P(ee_matrix)
    % desired position set
    x = ee_matrix(1, 4)
    y = ee_matrix(2, 4)
    z = ee_matrix(3, 4)
    
    % robot links length definition
    L = [1,1,0.5]
    
    if (x^2 + y^2 + z^2 > sum(L))
        error('asked position is out of workspace')
    end
    
    % finding roll pitch yaw from transformation matrix
    rpy = tr2rpy(ee_matrix, 'deg')
    
    % setting roll pitch yaw in radians
    pitch = rpy(2) * pi /180
    roll = rpy(1) * pi /180
    yaw = rpy(3) * pi /180
    
    % finding the coordinates of the pyatka
    P_x = x - L(3) * sin(pitch)
    P_y = y - L(3) * cos(yaw) * cos(pitch)
    P_z = z - L(3) * sin(yaw) * cos(pitch)
    
    % temp variable - the length from the base to the pyatka
    L_12 = sqrt(P_x^2 + P_y^2 + P_z^2)
    
    % defining the angle of knee joint
    q4 = acos((L_12^2 - ((L(1))^2 + (L(2))^2)) / (2 * L(1) * L(2)))
    
    % the angle between base-pyatka and base-knee
    alpha = asin(L(2) * sin(q4) / L_12)
    L_11 = L(1) * cos(alpha)
    % coefficient for the point of the height from the knee to th’ base-pyatka
    n = L_11 / L_12
    
    % definition of the coordinates of under knee point
    pk_1 = n * P_x
    pk_2 = n * P_y
    pk_3 = n * P_z
    
    % radius-vector of under knee point
    Pk = [pk_1, pk_2, pk_3]
    
    % the length of radius-vector of under knee point
    Pk_mod = sqrt((Pk(1))^2 + (Pk(2))^2 + (Pk(3))^2)
    % the height from the knee to base - pyatka
    h = L(1) * sin(alpha)
    
    beta = asin(Pk(3) / L_11)
    gamma = acos(Pk(2) / (L_11 * cos(beta)))
    
    k0_1 = h * sin(beta) * sin(gamma) + Pk(1)
    k0_2 = h * sin(beta) * cos(gamma) + Pk(2)
    k0_3 = h * cos(beta) + Pk(3)
    
    K0 = [k0_1, k0_2, k0_3]
    
    q2 = gamma
    q3 = beta
    
    rot_axes = Pk ./ Pk_mod
    
    % matrix defenition to rotate around base - under knee point 
    rm_11 = cos(roll) + (1 - cos(roll)) * (rot_axes(1))^2
    rm_12 = rot_axes(1) * rot_axes(2) * (1 - cos(roll)) - rot_axes(3) * sin(roll)
    rm_13 = rot_axes(1) * rot_axes(3) * (1 - cos(roll)) + rot_axes(2) * sin(roll)
    
    rm_21 = rot_axes(2) * rot_axes(1) * (1 - cos(roll)) + rot_axes(3) * sin(roll)
    rm_22 = cos(roll) + (rot_axes(2))^2 * (1 - cos(roll))
    rm_23 = rot_axes(2) * rot_axes(3) * (1 - cos(roll)) - rot_axes(1) * sin(roll)
    
    rm_31 = rot_axes(3) * rot_axes(1) * (1 - cos(roll)) - rot_axes(2) * sin(roll)
    rm_32 = rot_axes(3) * rot_axes(2) * (1 - cos(roll)) + rot_axes(1) * sin(roll)
    rm_33 = cos(roll) + (1 - cos(roll)) * (rot_axes(3))^2
    
    % full arbitrary axes rotation matrix
    rotation_matrix = [rm_11 rm_12 rm_13; rm_21 rm_22 rm_23; rm_31 rm_32 rm_33]
    % radius-vector knee
    K = transpose(rotation_matrix * transpose(K0))
    
    % radius-vector golen
    golen = [P_x P_y P_z] - K
    % the length of golen
    golen_mod = sqrt((golen(1))^2 + (golen(2))^2 + (golen(3))^2)  
    lambda = acos( (K(3) - Pk(3)) / sqrt((K(1))^2 + (K(2))^2 + (K(3))^2))
    nu = (K(1) - Pk(1)) / sqrt((K(1))^2 + (K(2))^2 + (K(3))^2) / sin(lambda) 
    q5 = acos(((L(2))^2 + (L(3))^2 - golen_mod ^ 2) / (2 * L(2) * L(3)))
    q6 = yaw + nu
    out = [roll, q2, q3, q4, q5, q6]
    
    % draw the result
    WHERE(out)
end