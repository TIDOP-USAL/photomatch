TEMPLATE = subdirs

# Al ejecutar los test da error el fichero fme_global.h porque no encuentra config_fme.h
# No entiendo porque ya que compilan y aparentemente esa cabecera esta desactivada
# Genero una cabecera simplemente para compatibilidad con el proyecto de CMAKE que si
# necesita esta cabecera y funciona correctamente
FME_MAJOR_VERSION = 2
FME_MINOR_VERSION = 0
FME_VERSION = $${FME_MAJOR_VERSION}"."$${FME_MINOR_VERSION}
#QMAKE_SUBSTITUTES += config_fme.h.in

SUBDIRS += \
    test \
    src
