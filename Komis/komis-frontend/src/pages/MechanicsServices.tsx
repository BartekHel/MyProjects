import React, { useContext, useEffect, useState } from 'react';
import '../css/ServiceOrder.css';
import ApiClient from '../service/ApiClient';
import userContext from '../PageInfo';
import Vehicle from "../entity/Vehicle";
import { Link } from 'react-router-dom';

const MechanicsServices = () => {
  const apiClient = new ApiClient();
  const { userId } = useContext(userContext);
  const [ownedCars, setOwnedCars] = useState<Vehicle[]>([]);
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);

  const fetchServices = async () => {
    try {
      const services = await apiClient.GetMechanicServices(userId);
      setOwnedCars(services);
    } catch (err) {
      setError("Error fetching client services");
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {

    fetchServices();

  }, [userId]);

  const handleDateChange = async (event, id: number) => {
    try {
      await apiClient.SetServiceDate(id, event.target.value);
      setOwnedCars(prevCars => 
        prevCars.map(car => 
          car.service_id === id ? { ...car, execution_date: event.target.value } : car
        )
      );
      fetchServices();
    } catch (err) {
      setError("Error setting new date");
    } finally {
      setLoading(false);
    }
  }

  const handlePriceChange = async (event, id: number) => {
    try {
      await apiClient.SetServicePrice(id, event.target.value);
      setOwnedCars(prevCars => 
        prevCars.map(car => 
          car.service_id === id ? { ...car, execution_date: event.target.value } : car
        )
      );
      fetchServices();
    } catch (err) {
      setError("Error setting new date");
    } finally {
      setLoading(false);
    }
  }

  if (loading) {
    return <div id="serviceOrderContainer">Loading...</div>;
  }

  if (error) {
    return <div id="serviceOrderContainer">{error}</div>;
  }

  
  

  return (
    <div id="serviceOrderContainer">
      <table>
        <thead>
          <tr>
            <th>Admission date</th>
            <th>Execution date</th>
            <th>Description</th>
            <th>Price</th>
          </tr>
        </thead>
        <tbody>
          {ownedCars.map((service, index) => (
            <tr key={index}>
              <td>{service.admission_date}</td>
              <td>
                {
                  <input
                  type="date"
                  id="date-picker"
                  value={service.execution_date || ''} // Ensure execution_date is handled correctly
                  onChange={(event) => handleDateChange(event, service.service_id)}
                  />
                }
                
              </td>
              <td>{service.description}</td>
              <td>
              {
                  <input
                  type="number"
                  value={service.price || ''}
                  onChange={(event) => handlePriceChange(event, service.service_id)}
                  />
                }
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default MechanicsServices;