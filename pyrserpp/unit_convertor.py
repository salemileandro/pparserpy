class UnitConvertor:
    """
    Small class that allows for the easy conversion between two different units. When a conversion is added, the
    inverse conversion is also automatically added !
    UnitConvertor class. It defines an object that can be used to convert a quantity from one unit to another
    """
    def __init__(self):
        self.__converter = {}

    def add_unit(self, external_unit: str, internal_unit: str, conversion: float):
        """
        Teach the UnitConvertor object a new unit conversion. The inverse conversion is also
        defined automatically. I also learn the unit conversion (same unit -> conversion = 1.0)

        :param external_unit:   str     Name of the external unit, i.e. the origin unit
        :param internal_unit:   str     Name of the internal unit, i.e. the target unit
        :param conversion:  str/float   Conversion factor (if str, automatic cast on float)
        :return:
        """

        if isinstance(conversion, str):
            conversion = float(conversion)

        # Add the direct conversion
        if external_unit not in self.__converter:
            self.__converter[external_unit] = {}
        self.__converter[external_unit][internal_unit] = conversion

        # Add the inverse conversion
        if internal_unit not in self.__converter:
            self.__converter[internal_unit] = {}
        self.__converter[internal_unit][external_unit] = 1.0 / conversion

        # Add the direct unitary conversion ( 1 "unit" = 1 "unit" )
        if external_unit not in self.__converter:
            self.__converter[external_unit] = {}
        self.__converter[external_unit][external_unit] = 1.0

        # Add the inverse unitary conversion ( 1 "unit" = 1 "unit" )
        if internal_unit not in self.__converter:
            self.__converter[internal_unit] = {}
        self.__converter[internal_unit][internal_unit] = 1.0

    def is_convertible(self, external_unit: str, internal_unit: str) -> bool:
        """
        Check if the unit conversion external -> internal is possible using the UnitConvertor object

        :param external_unit: str   External unit (user unit)
        :param internal_unit: str   Internal unit (cpp program unit)
        :return:                    True if conversion possible, False otherwhise
        """
        if external_unit in self.__converter:
            if internal_unit in self.__converter[external_unit]:
                return True
        return False

    def __getitem__(self, item: str) -> dict:
        """
        Overloading the [] operator for user friendly access to UnitConvertor object.
        The conversion factor can be accessed in this way (3rd line of the following code)
            x = UnitConvertor()             # Creation of the UnitConvertor object
            x.add_unit("fs", "s", 1e-15)    # Adding the definition of conversion between femtoseconds to seconds
            fs_to_s = x["fs"]["s"]          # Fetching the conversion factor using the bracket operator
        :param item: origin unit
        :return:
        """
        return self.__converter[item]

    def __str__(self):
        a = "\n"
        for i in self.__converter:
            for j in self.__converter[i]:
                a += "%s -> %s = %.6e\n" % (i, j, self.__converter[i][j])
        return a


if __name__ == "__main__":

    x = UnitConvertor()

    x.add_unit("fs", "s", 1e-15)
    x.add_unit("ns", "s", 1e-9)
    x.add_unit("ms", "s", 1e-3)


    print("Printing available conversions :")
    print(x)

    print("Testing the can_i_convert function :")
    units = ["fs", "ns", "s"]
    for i in units:
        for j in units:
            print("Can I convert %s to %s ? %d" %(i, j, x.is_convertible(i,j)))