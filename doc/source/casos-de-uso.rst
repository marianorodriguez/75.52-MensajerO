Casos de uso
============


Registrarse
-----------

**Pre**: El usuario no inició sesión.

**Post**: Se agrega un usuario nuevo a la base de datos del servidor.

* Cliente envía un post con el nombre de usuario con el que quiere registrarse y una contraseña.
* Servidor captura e interpreta request.
* Servidor verifica que el usuario nuevo no exista:

  * Si se puede crear, devuelve ok.
  * Si existe o tienen un nombre inválido, devuelve error.


Login
-----

**Pre**: Ninguno.

**Post**: El cliente ingresa a la aplicación.

* Cliente ingresa los usuario y password.
* Cliente obtiene posición geográfica.
* Cliente envía post con los datos.
* Servidor valida datos del cliente.
* Servidor consulta el par usuario-password.
* Servidor responde al request.
* Cliente continúa en caso de éxito o pide reintento si falla
* Servidor actualiza estado de la última conexión (en caso de éxito).


Iniciar una conversación
------------------------

**Pre**: El cliente hizo login y está activo.

**Post**: El cliente tiene una conversación activa con el destinatario.

* Cliente selecciona el destinatario.
* Cliente solicita últimos mensajes con el destinatario.
* Servidor valida datos del cliente y responde la solicitud.
* Cliente muestra los últimos mensajes enviados (y recibidos), y fecha de última conexión del destinatario.


Enviar mensaje
--------------

**Pre**: El cliente hizo login y está activo. El cliente está en una conversación.

**Post**: Se renueva el periodo de actividad del cliente.

* Cliente ingresa el mensaje.
* Cliente envía un post con sus datos, mensaje y destinatario.
* Cliente solicita el id del último mensaje que recibió el servidor.
* Si el id del mensaje recibido no concuerda con el enviado, reenviar.
* Servidor encola el mensaje recibido en una lista de mensajes enviados al destinatario.


Recibir actualizaciones
-----------------------

**Pre**: El cliente hizo login y está activo.

**Post**: El cliente refresca su estado de activo, y actualiza datos de sus contactos.

* Cliente envía un request de actualización.
* Servidor responde con:

  * Mensajes nuevos enviados al cliente.
  * Cambios de perfil de los contactos.
  * Conexiones de contactos recientes.
  
* En caso de mensajes nuevos, el cliente notifica actualización.


Agregar contacto nuevo
----------------------

**Pre**: El cliente hizo login y está activo.

**Post**: El usuario puede iniciar conversación con el nuevo destinatario.

* Cliente ingresa el nombre de usuario al que quiere agregar como contacto.
* Servidor verifica que el contacto nuevo exista:

  * Si el contacto existe, devuelve ok.
  * Si el contacto no existe, devuelve error.


Cambiar de estado
-----------------
 
**Pre**: El cliente hizo login y está activo.

**Post**: El cliente refresca su estado de activo, y cambia su información (estado).
 
* Cliente envía un post con su estado nuevo.
* Servidor valida el request del cliente.

  * Si el estado es válido, cambia la información del cliente y encola el cambio en los usuarios que lo poseen como contacto.
  * Si el estado es inválido, no se produce actualización.

