
interface Props{
    modificationChange:(newTotalPrice:number)=>void;
    wasSold:boolean;
}

function Filters({modificationChange,wasSold}: Props) {
  const detailingOptions = [
    { name: "Interior Shampooing", price: 100 },
    { name: "Exterior Waxing", price: 150 },
    { name: "Wheel Polishing", price: 120 },
  ];

  const mechanicalOptions = [
    { name: "Lubrication System Upgrade", price: 300 },
    { name: "Gas system instalation", price: 200 },
    { name: "Transmission Service", price: 250 }
  ];


  const upholsteryOptions = [
    { name: "Fabric upholstery", price: 0 },
    { name: "Premium Leather upholstery", price: 800 }
  ];

  const handleModificationChange = () => {
    let totalPrice = 0;
  
    detailingOptions.forEach((option) => {
      const checkbox = document.getElementById(option.name) as HTMLInputElement; 
      if (checkbox.checked) {
        totalPrice += option.price; 
      }
    });

    mechanicalOptions.forEach((option) => {
      const checkbox = document.getElementById(option.name) as HTMLInputElement; 
      if (checkbox.checked) {
        totalPrice += option.price; 
      }
    });
  
    const upholsterySelect = document.querySelector('select[name="upholstery"]') as HTMLSelectElement;
    const selectedUpholstery = upholsterySelect.value;
    const selectedUpholsteryPrice = upholsteryOptions.find(option => option.name === selectedUpholstery)?.price || 0;
    totalPrice += selectedUpholsteryPrice;
    
    modificationChange(totalPrice);
  }


  
  return (
    <div className='filters'>
      <div className='filter'>
        <label>Detailing</label>
        {detailingOptions.map((option) => 
        <span style={{width:'100%',display:'flex',justifyContent:'space-between'}}>
          <p>{option.name} {option.price}&euro;</p>
        {!wasSold &&<input style={{width:'30px'}} type="checkbox" id={option.name} onChange={handleModificationChange}  value={option.price}/>}
        </span>)}
        </div>
      <div className='filter'>
        <label>Mechanic features</label>
        {mechanicalOptions.map((option) => 
        <span style={{width:'100%',display:'flex',justifyContent:'space-between'}}>
          <p>{option.name} {option.price}&euro;</p>
        {!wasSold &&<input style={{width:'30px'}} type="checkbox" onChange={handleModificationChange}  id={option.name}  value={option.price}/>}
        </span>)}
      </div>
      <div className='filter'>
        <label>Upholstery</label>
        {!wasSold ?<select name="upholstery" onChange={handleModificationChange}>
          {upholsteryOptions.map((option) => (
            <option key={option.name} value={option.name}>{option.name} {option.price}&euro;</option>
          ))}
        </select>
        : 
        <>
        {  upholsteryOptions.map((option) =><span style={{width:'100%',display:'flex',justifyContent:'space-between'}}>
          <p>{option.name} {option.price}&euro;</p>
          </span>)}
        </>
        }
      </div>
    </div>
  );
}

export default Filters;
