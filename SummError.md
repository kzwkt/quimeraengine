# Convención de Manejo de Errores #

  * Las excepciones deben tirarse por valor (throw exception();) y capturarse por referencia constante (catch(const exception& ex)).
  * Usar el manejador de errores para devolver información de error de las funciones.
  * Usar excepciones para casos graves que impidan la ejecución del motor.