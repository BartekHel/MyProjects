import axios from "axios";
import Vehicle from "../entitiy/Vehicle";

export interface VehicleWithPicture {
  vehicle: Vehicle;
  picture: string | null;
}

  class ApiMainPage{
    constructor(){}

    GetVehicles = async (): Promise<VehicleWithPicture[]> => {
      try {
          const resp = await axios.get('http://localhost:8080/car-shop/vehicles');
          const vehicles = resp.data;

          const allVehicles = await Promise.all(vehicles.map(async (vehicle: Vehicle) => {
              try {
                  const pictureResp = await axios.get(`http://localhost:8080/car-shop/vehicles/${vehicle.vehicle_id}/picture`);
                  const picture = pictureResp.data;

                  return {
                      vehicle: vehicle,
                      picture: picture
                  } as VehicleWithPicture;
              } catch (error) {
                  console.error(`Error fetching picture for vehicle ${vehicle.vehicle_id}:`, error);
                  return {
                      vehicle: vehicle,
                      picture: null
                  } as VehicleWithPicture;
              }
          }));

          return allVehicles;

      } catch (error) {
          console.error("Error fetching all vehicles:", error);
          throw error;
      }
    };

    GetFilteredAndSortedVehicles = async (phrase: string, minPrice: number, maxPrice: number, sort: string): Promise<VehicleWithPicture[]> => {
      try {
        let resp;
        if (sort == "none" && phrase.trim() == "" && minPrice == 0 && maxPrice == 0)
          resp = await axios.get('http://localhost:8080/car-shop/vehicles');
        else {
          if (maxPrice == 0)
            maxPrice = 999999999;
            resp = await axios.get(`http://localhost:8080/car-shop/vehicles/filtered`, {
              params: { marka: "", cenamin: minPrice, cenamax: maxPrice, sortby: sort, input: phrase}
            });
        }
        const vehicles = resp.data;

        const allVehicles = await Promise.all(vehicles.map(async (vehicle: Vehicle) => {
          try {
              const pictureResp = await axios.get(`http://localhost:8080/car-shop/vehicles/${vehicle.vehicle_id}/picture`);
              const picture = pictureResp.data;
              console.log(picture);
              return {
                  vehicle: vehicle,
                  picture: picture
              } as VehicleWithPicture;
          } catch (error) {
              console.error(`Error fetching picture for vehicle ${vehicle.vehicle_id}:`, error);
              return {
                  vehicle: vehicle,
                  picture: null
              } as VehicleWithPicture;
          }
        }));

        return allVehicles;
      } catch (error) {
        console.error("Error fetching searched vehicles:", error);
        throw error;
      }
    };
  }

  export default ApiMainPage;