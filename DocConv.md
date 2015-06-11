# Convenciones de Documentación #

Dado que la documentación será generada mediante la herramienta para C++ Doxygen, tendremos que adoptar un patrón que pueda analizar. Para hacerlo más estándar, utilizaremos notación XML, utilizada ampliamente en proyectos .Net, con algunas excepciones.

## Etiqueta summary ##
Descripción del elemento a documentar (método, atributo, constructor, enumerador, clase, etc.). Puede ser desde un par de palabras a unos cuantos párrafos, según el caso.
```
/// <summary>
/// 
/// </summary>
```

## Etiqueta remarks ##
Información adicional que el desarrollador deba conocer, normalmente detalles técnicos o peculiaridades de funcionamiento. Se escribe, si cabe, a continuación de _summary_ y antes del resto de etiquetas.
```
/// <remarks>
/// 
/// </remarks>
```

## Etiqueta param ##
Descripción de un parámetro de un método o función. Puede ser desde un par de palabras a unos cuantos párrafos, según el caso. Esta etiqueta tiene un atributo "name", que debe ser rellenado con el nombre del parámetro. Las etiquetas _param_ van a continuación de _summary_. No se especificará el tipo, aunque sí se hará saber si es opcional mediante una etiqueta `[Opcional]`, y si es de entrada o salida, con `[IN]`, `[OUT]` ó `[IN/OUT`].
```
/// <param name=""> [Opcional][IN]-[OUT]-[IN/OUT] </param>
```


## Etiqueta returns ##
Descripción del resultado de la función o método. Puede ser desde un par de palabras a unos cuantos párrafos, según el caso. Evidentemente, sólo aparece si el valor a devolver no es de tipo _void_. Debe colocarse después de las etiquetas _summary_ y _param_.
```
/// <returns>
/// 
/// </returns>
```

## Etiqueta exception ##
Mención de un tipo de excepción que puede ser elevada por una función o método. No es obligatoria su descripción. Esta etiqueta tiene un atributo "cref", el cual hay que rellenar con el tipo de la excepción. Debe aparecer después del resto de etiquetas.
```
/// <exception cref=""></exception>
```


## Enumeradores ##
Los enumeradores tendrán, además de la etiqueta summary, una serie de comentarios por cada valor enumerado. Estos comentarios no se corresponden con ninguna notación XML, pero sí son interpretados por Doxygen.
```
/// <summary>
///
/// </summary>
enum Enumerado
{
   Valor1, /*!< Descripción */
   Valor2  /*!< Descripción */
};
```