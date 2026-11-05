# Compilación linux
Ejecuta el script compile.sh para compilar el proyecto en bin
El argumento "run" ejecutará el juego nada más compilarlo
# Requisitos

A)
    1) "SemiEulerSystem.c" todo el archivo
    2) "ParticleSystem.c" línea 63 y "InputSystem.c" línea 38
    3) "SemiEulerSystem.c" líneas 6-9
B) "InputSystem.c" líneas 21-47
C) "ParticleSystem.c" todo el archivo
D)
    1) "ParticleSystem.c" línea 13. Aunque se modifican los componentes durante todo el archivo
    2) "ParticleSystem.c" línea 29 y 59
    3) "main.c" línea 61. se pueden crear sistemas de partículas simplemente creando una entidad y asignando la etiqueta PARTICLE_SYSTEM y los componentes correspondientes. 
E)
    1) los sistemas "GravityForceGenratorSystem.c", "ExplosionForceGeneratorSystem.c", "WindForceGeneratorSystem.c" y "WhirlwindForceGenrerator.c" son los sistemas encargados de la lógica de las fuerzas.
    2) idem anterior.
    3) idem anterior.
    4) idem anterior. (en los sistemas de fuerza están implementadas las lógicas).

# Resumen

La arquitectura itera sobre todas las entidades y comprueba las máscaras de cada una. Si la máscara coincide con el sistema que se quiere procesar, se procesa esa entidad.
El flujo de ejecución es una pipeline en la que cada los sistemas procesan los datos de las partículas uno detrás del otro.

