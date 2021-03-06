#ifndef _HELMET_FACTORY_H
#define _HELMET_FACTORY_H

#include "server_helmet.h"
#include "server_iron_helmet.h"
#include "server_hood.h"
#include "server_magic_hat.h"
#include "server_default_helmet.h"

/* Clase que funciona como factory para los distintos tipos de cascos de la aplicacion */
class HelmetFactory {
public:

    /* Recibiendo un id crea el casco correspondiente */
    static Helmet make_helmet(const uint8_t helmet_id, Json::Value& config);
};

#endif // _HELMET_FACTORY_H
