from typing import TYPE_CHECKING


class AppObject:

    """
    classe mère pour tous les managers et serveurs afin d'avoir accés à l'application
    """
    if TYPE_CHECKING:
        from app import Application
        app : Application = None

    def finishEvent(event):
        pass

    @classmethod
    def __initClass__(cls,app):
        cls.app=app
