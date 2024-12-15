clear;
clc;

% Longitudes de los eslabones
l2 = 12; % Longitud del primer eslabón rotativo
l3 = 12; % Longitud del segundo eslabón rotativo
elevacion_base = 5; % Elevar el robot 5 cm desde el suelo

% Definición de las articulaciones del robot
L1 = Prismatic('theta', 0, 'a', 0, 'alpha', 0, 'qlim', [0 15]); % Movimiento prismático en z
L2 = Revolute('d', 0, 'a', l2, 'alpha', 0); % Primer eje rotativo (en el plano XZ)
L3 = Revolute('d', 0, 'a', l3, 'alpha', 0); % Segundo eje rotativo (en el plano XZ)

% Ensamblar el manipulador
R = SerialLink([L1, L2, L3], 'name', 'Robot cilindrico');

% Definir los valores de q1, q2, q3 para simular el movimiento
q1_vals = linspace(elevacion_base + 4.5, elevacion_base + 10, 50); % Valores para el movimiento prismático en Z
q2_vals = linspace(0, pi/2, 50);  % Valores para el primer ángulo rotativo (en radianes)
q3_vals = linspace(0, -pi/2, 50);  % Valores para el segundo ángulo rotativo (en radianes)

% Crear una figura para la animación
figure;
hold on;
axis([-30 30 -30 30 0 30]); % Limitar el espacio de la visualización
xlabel('X'); ylabel('Y'); zlabel('Z');
grid on;

% Para almacenar las posiciones del efector final
efector_final_trajectory = [];

% Para cada conjunto de q1, q2, q3, calcular las posiciones y mover el robot
for i = 1:length(q1_vals)
    q1 = q1_vals(i);
    q2 = q2_vals(i);
    q3 = q3_vals(i);

    % Calcular las posiciones del efector final usando la Cinemática Directa
    [x, y, z] = Cinematica_Directa(q1, q2, q3, l2, l3);

    % Mostrar los valores calculados
    disp(['x = ', num2str(x)]);
    disp(['y = ', num2str(y)]);
    disp(['z = ', num2str(z)]);

    % Crear el vector q para las articulaciones
    q = [q1, q2, q3];

    % Actualizar la visualización del robot
    R.plot(q); % Mostrar el robot en su nueva configuración

    % Almacenar la posición del efector final
    efector_final_trajectory = [efector_final_trajectory; x, y, z];

    % Graficar el trazo del efector final
    plot3(efector_final_trajectory(:,1), efector_final_trajectory(:,2), efector_final_trajectory(:,3), 'r'); % Trazo en rojo

    % Pausa para que se vea la animación
    pause(0.1); % Puedes ajustar el tiempo para acelerar o ralentizar la animación
end

