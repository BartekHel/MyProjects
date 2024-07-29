import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './pages/MainPage.tsx'
import './index.css'
import Login from './pages/Login.tsx'
import Register from './pages/Register.tsx'
import Navbar from './components/Navbar.tsx'
import { BrowserRouter } from 'react-router-dom'
import RoutesManager from './pages/RoutesManager.tsx'

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    
      <BrowserRouter>
        <RoutesManager/>
      </BrowserRouter>
    
    
    
  </React.StrictMode>,
)
