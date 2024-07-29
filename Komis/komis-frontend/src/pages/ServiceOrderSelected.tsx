import React, { useContext, useEffect, useState } from 'react';
import '../css/ServiceOrder.css';
import ApiClient from '../service/ApiClient';
import userContext from '../PageInfo';
import Vehicle from "../entity/Vehicle";
import { Link, useParams } from 'react-router-dom';


const ServiceOrderSelected = () => {
  const { carId } = useParams();
  const [ respInfo, setRespInfo ] = useState();
  const [ desc, setDesc ] = useState("");
  const [ repairerId, setRepairerId ] = useState(0);
  const [ repairerName, setRepairerName ] = useState("");
  const [selectedDate, setSelectedDate] = useState<string>('');
  const apiClient = new ApiClient();
  const { userId } = useContext(userContext);
  const [selectedCar, setSelectedCar] = useState<Vehicle>();
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);
  
  const handleDateChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setSelectedDate(event.target.value);
  };

  const handleDescChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setDesc(event.target.value);
  };

  const handleOrderService = async () => {
    try {
      const resp = await apiClient.PostService(selectedCar.vehicle_id, repairerId, desc);
      setRespInfo(resp);
    } catch (err) {
      console.log(err.message);
      setError("Error ordering service");
    } finally {
      setLoading(false);
    }
  };
  

  console.log("carId");
  console.log(carId.substring(1));

  useEffect(() => {
    const fetchClientVehicles = async () => {
      try {
        const vehicle = await apiClient.GetVehicleById(carId.substring(1));
        setSelectedCar(vehicle);
        console.log(selectedCar);
      } catch (err) {
        console.log(err.message);
        setError("Error fetching client vehicles");
      } finally {
        setLoading(false);
      }
    };

    fetchClientVehicles();
  }, []);

  useEffect(() => {
    const fetchRepirer = async () => {
      try {
        const repairer = await apiClient.GetLeastOccupiedReapirer();
        setRepairerId(repairer[0]);
        setRepairerName(repairer[1]);
      } catch (err) {
        console.log(err.message);
        setError("Error fetching repairer");
      } finally {
        setLoading(false);
      }
    };

    fetchRepirer();
  }, []);

  if (loading) {
    return (
        <div id="serviceOrderContainer">
            <h3>Loading...</h3>
        </div>
    );
    
  }

  if (error) {
    return (
        <div id="serviceOrderContainer">
            <h3>{error}</h3>
        </div>
    );
  }

  console.log(selectedCar);

  return (
    
    <div id="serviceOrderContainer">
        
        <h3>Brand: {selectedCar.brand}</h3>
        <h3>Model: {selectedCar.model}</h3>
        <h3>Modifications: {selectedCar.modifications}</h3>
        <h3>Next inspection date: {selectedCar.next_inspection_date}</h3>
        <h3>Repairer: {repairerName}</h3>
        {/*<h3>Choose a date:</h3>
        <input
            type="date"
            id="date-picker"
            value={selectedDate}
            onChange={handleDateChange}
        />
  <h3>Selected Date: {selectedDate}</h3>*/}
        <h3>Description:</h3>
                <input
                    value={desc}
                    onChange={handleDescChange}
                />

        {
            //if(respInfo!=null)
            
            <h3>{respInfo==null ? "" : respInfo ? "Success ordering service" : "Error during ordering service"}</h3>
            
        }
        
        <button onClick = {handleOrderService}>Confirm</button>

    </div>
  );
};

export default ServiceOrderSelected;