function [q1, q2, q3] = Cinematica_Inversa(x, y, z)
    % Parámetros del robot
    l1 = 10.5; % Longitud del primer eslabón (en cm)
    l2 = 13.5; % Longitud del segundo eslabón (en cm)
    
    % Cinemática Inversa
    q1 = z;  % El valor de q1 es simplemente la coordenada Z

    % Calculamos q2 y q3 usando las fórmulas proporcionadas
    C3 = (x^2 + y^2 - l1^2 - l2^2) / (2 * l1 * l2);  % C3
    S3 = sqrt(1 - C3^2);  % S3

    q3 = atan2(S3, C3);  % ángulo q3
    q2 = atan2(y, x) - atan2(l2 * sin(q3), l1 + l2 * cos(q3));  % ángulo q2
end

