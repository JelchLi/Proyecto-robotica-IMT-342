function [x, y, z] = Cinematica_Directa(q1, q2, q3, l1, l2)
    % Cinemática Directa para el robot cilíndrico
    % Cálculos de la posición del efector final
    x = l1 * cos(q2) + l2 * cos(q2 + q3);
    y = l1 * sin(q2) + l2 * sin(q2 + q3);
    z = q1; % Movimiento prismático
end
