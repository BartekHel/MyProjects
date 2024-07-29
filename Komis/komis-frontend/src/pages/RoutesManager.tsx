import React from 'react'
import Navbar from '../components/Navbar'
import { Route, Routes } from 'react-router-dom'
import App from './MainPage'
import Login from './Login'
import Register from './Register'
import CarDetailsComponent from './CarDetailsComponent'
import { UserProvider } from '../PageInfo'
import ServiceOrder from './ServiceOrder'
import ManagerPage from './ManagerPage'
import ServiceOrderSelected from './ServiceOrderSelected'
import MechanicsServices from './MechanicsServices'
import { ToastContainer } from 'react-toastify'
import AddPage from './AddPage'
import DealersTransactions from '././DealersTransactions'

const RoutesManager = () => {
  return (
    <div>
      <UserProvider>
      <Navbar/>
      <Routes>
        <Route path="/" element={<App/>}/>
        <Route path="/login" element={<Login/>}/>
        <Route path="/register" element={<Register/>}/>
        <Route path="/managerPanel/:userId" element={<ManagerPage/>}/>
        <Route path="/carDetails/:carId" element={<CarDetailsComponent/>}/>
        <Route path="/orderService" element={<ServiceOrder/>}/>
        <Route path="/orderServiceSelected/:carId" element={<ServiceOrderSelected/>}/>
        <Route path="/mechanicsServices" element={<MechanicsServices/>}/>
        <Route path="/addPage" element={<AddPage/>}/>
        <Route path="/dealersTransactions" element={<DealersTransactions/>}/>
      </Routes>
      </UserProvider>
    </div>
  )
}

export default RoutesManager;
