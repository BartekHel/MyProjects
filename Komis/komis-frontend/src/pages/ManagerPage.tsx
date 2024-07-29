import React from 'react'
import '../css/ManagerPage.css'
import html2canvas from 'html2canvas';
import jsPDF from 'jspdf';
import { useParams } from 'react-router-dom';

interface Employee {
    name: string;
    email: string;
    earnings: string;
}

const ManagerPage = () => {
    const {userId}=useParams();
    const [option,setOption] = React.useState(1);
    const [employees,setEmployees] = React.useState([] as Employee[]);
    const [showrooms,setShowrooms] = React.useState([] as {name:string,earnings:number}[]);

    React.useEffect(()=>{
        const fetchData = async () => {
            try {
                const response = await fetch(`http://localhost:8080/car-shop/manager/${userId}/employees/money?year=-1&month=-1`);
                const data = await response.json();
                setEmployees(data);
            } catch (error) {
                console.error("Error fetching the employees:", error);
            }
        }
        fetchData();
    },[])

    React.useEffect(()=>{
        const fetchData = async () => {
            try {
                const response = await fetch(`http://localhost:8080/car-shop/showrooms`);
                const data = await response.json();
                setShowrooms(data.map((showroom:{address:string,profitLastMonth:number})=>({name:showroom.address,earnings:showroom.profitLastMonth})));
            } catch (error) {
                console.error("Error fetching the employees:", error);
            }
        }
        fetchData();
    },[])



    const handleDownloadRaport = () => {
        const input = document.getElementById("Report");
    
        html2canvas(input!, { logging: true, useCORS: true, scale: 2 }).then(canvas => {
            const imgWidth = 210;
            const pageHeight = 295; // Height of an A4 page in mm (210mm x 297mm, leaving some margin)
            const imgHeight = canvas.height * imgWidth / canvas.width;
            const imgData = canvas.toDataURL("image/png", 1.0);
            const pdf = new jsPDF('p', 'mm', 'a4');
            let position = 0;
    
            if (imgHeight <= pageHeight) {
                // If the content fits on one page
                pdf.addImage(imgData, 'PNG', 0, 0, imgWidth, imgHeight);
            } else {
                // If the content is too large, split it into multiple pages
                let remainingHeight = imgHeight;
                while (remainingHeight > 0) {
                    pdf.addImage(imgData, 'PNG', 0, position, imgWidth, imgHeight);
                    remainingHeight -= pageHeight;
                    position -= pageHeight; // Move position up for the next page
                    if (remainingHeight > 0) {
                        pdf.addPage();
                    }
                }
            }
    
            pdf.save('raport.pdf');
        });
    }
    



    return (
        <div className='wrapper'>
            <div className='manager-page-wrapper'>
                <h5>{option==1?'Employee List':'Showroom List'}</h5>

                <div className='button-wrapper'>
                <button className='show' onClick={()=>setOption(1)}>Show Employee List</button>
                <button className='show' onClick={()=>setOption(2)}>Showroom List</button>
                </div>

                <button id='downloadButton' onClick={handleDownloadRaport}>Download Report</button>

                <div id='Report'>
                <div className='employeePanel'>
                   <div className='employeeLabel'>
                    <p>{option==1?'Employee':'Showroom'}</p>
                    <p>Earnings</p>
                    </div>
                <div className='employeeList'>
                    {option==1?
                    <>
                    {employees.map((employee, index) => (
                        <div  key={index}>
                            <p>{employee.name}</p>
                            <p>{employee.email}</p>
                            <p>{employee.earnings}$</p>
                        </div>
                    ))}
                    </>
                    :
                    <>
                    {showrooms.map((showroom, index) => (
                        <div  key={index}>
                            <p>{showroom.name}</p>
                            <p>{showroom.earnings}$</p>
                        </div>
                    ))}
                    </>
                    }
                </div>
                </div>
                </div>
            </div>
        </div>
    );
}

export default ManagerPage