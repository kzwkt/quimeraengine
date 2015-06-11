# Fase 0 #

## Objetivos ##

  * Tener una base sólida, de confianza, sobre la que construir nuestra librería al completo.
  * Implementar todas las clases auxiliares trasversales, totalmente aisladas del motor. Tales clases deberían tener las mínimas dependencias externas posibles, no encapsulando objetos de otras librerías (salvo la STL, obviamente) y evitando particularidades de los sistemas, aunque más de una vez será inevitable.
  * Partir de una base optimizada.
  * Disponer de las secciones trasversales del motor.
  * Disponer de las secciones que nos permiten obtener datos del motor e introducirlos en tiempo de ejecución.


## Prioridades ##

  * [Diseño]: Minimización de dependencias.
  * [Diseño]: Usabilidad.
  * [Diseño]: Endurance, exploratory y stress tests.
  * [Código]: Documentación interna en los métodos, especialmente cuando se codifique de forma poco clara en pos de optimizaciones.
  * [Código]: Optimización de velocidad.
  * [Código]: Código claro (self-explained o con documentación abundante y útil).
  * [Código]: Unit tests de amplia cobertura.