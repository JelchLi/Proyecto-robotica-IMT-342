% Definir las coordenadas deseadas
x = 10;  % Coordenada X
y = 10;  % Coordenada Y
z = 5;  % Coordenada Z

% Llamar a la función de Cinemática Inversa con los valores de x, y, z
[q1, q2, q3] = Cinematica_Inversa(x, y, z);

% Mostrar los valores calculados de q1, q2, y q3
disp(['q1 = ', num2str(q1)]);
disp(['q2 = ', num2str(q2)]);
disp(['q3 = ', num2str(q3)]);

