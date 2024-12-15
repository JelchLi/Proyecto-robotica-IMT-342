clear;
clc;

% Longitudes de los eslabones
l2 = 10.5; % Longitud del primer eslabón rotativo
l3 = 13.5; % Longitud del segundo eslabón rotativo
elevacion_base = 5; % Elevar el robot 5 cm desde el suelo

% Definición de las articulaciones del robot
L1 = Prismatic('theta', 0, 'a', 0, 'alpha', 0, 'qlim', [0 15]); % Movimiento prismático en z
L2 = Revolute('d', 0, 'a', l2, 'alpha', 0); % Primer eje rotativo (en el plano XZ)
L3 = Revolute('d', 0, 'a', l3, 'alpha', 0); % Segundo eje rotativo (en el plano XZ)

% Ensamblar el manipulador
R = SerialLink([L1, L2, L3], 'name', 'Robot cilindrico');

% Definir los valores de x, y, z para simular el movimiento
x_vals = linspace(24, 0, 50);  % Generamos valores para el movimiento en X
y_vals = linspace(0, 15, 50);  % Generamos valores para el movimiento en Y
z_vals = linspace(elevacion_base, elevacion_base + 14, 50);  % Generamos valores para el movimiento en Z

% Crear una figura para la animación
figure;
hold on;
axis([-30 30 -30 30 0 30]); % Limitar el espacio de la visualización

% Para almacenar las posiciones del efector final
efector_final_trajectory = [];

% Para cada valor de x, y, z, calcular los ángulos y mover el robot
for i = 1:length(x_vals)
    x = x_vals(i);
    y = y_vals(i);
    z = z_vals(i);  % El valor de Z siempre se eleva desde la base

    % Calcular los valores de q1, q2 y q3 usando la Cinemática Inversa
    [q1, q2, q3] = Cinematica_Inversa(x, y, z);
    
    % Convertir q2 y q3 de radianes a grados
    q2_deg = rad2deg(q2);
    q3_deg = rad2deg(q3);
    
    % Mostrar los valores calculados en grados
    disp(['q1 = ', num2str(q1)]);
    disp(['q2 = ', num2str(q2_deg), '°']);
    disp(['q3 = ', num2str(q3_deg), '°']);
    
    % Crear el vector q para las articulaciones
    q = [q1, q2, q3];  % Solo los ángulos, no es necesario incluir un eslabón extra

    % Actualizar la visualización del robot
    R.plot(q); % Mostrar el robot en su nueva configuración

    % Obtener la posición del efector final
    efector_final_pos = R.fkine(q).t; % Obtener la posición del efector final
    
    % Almacenar la posición del efector final
    efector_final_trajectory = [efector_final_trajectory; efector_final_pos(1), efector_final_pos(2), efector_final_pos(3)];
    
    % Graficar el trazo del efector final
    plot3(efector_final_trajectory(:,1), efector_final_trajectory(:,2), efector_final_trajectory(:,3), 'r'); % Trazo en rojo
    
    % Pausa para que se vea la animación
    pause(0.1);  % Puedes ajustar el tiempo para acelerar o ralentizar la animación
end
