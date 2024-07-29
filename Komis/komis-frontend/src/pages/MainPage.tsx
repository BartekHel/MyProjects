import { useEffect, useRef, useState } from "react";
import "../css/MainPage.css";
import { useNavigate } from "react-router-dom";
import ApiMainPage from '../service/ApiMainPage'
import Vehicle from "../entitiy/Vehicle";

export interface VehicleWithPicture {
  vehicle: Vehicle;
  picture: string | null;
}

function App() {
  const apiMainPage = new ApiMainPage();
  const [phrase, setPhrase] = useState("");
  const [minPrice, setMinPrice] = useState(0);
  const [maxPrice, setMaxPrice] = useState(0);
  const [sort, setSort] = useState("none");
  const [offers, setOffers] = useState<VehicleWithPicture[]>([]);
  const [showAll, setShowAll] = useState(false);
  const [showSpinner, setShowSpinner] = useState(false);
  const navigate = useNavigate();
  const topRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    fetchOffers();
    scrollToTop();
  }, []);

  const fetchOffers = async () => {
    try {
      setShowSpinner(true);
      const vehiclesWithPictures = await apiMainPage.GetVehicles();
      setOffers(vehiclesWithPictures);
      setShowSpinner(false);
      scrollToTop();
    } catch (error) {
      setShowSpinner(false);
      console.error("Error fetching offers:", error);
    }
  };

  const filterAndSortOffers = async (phrase: string, minPrice: number, maxPrice: number, sort: string) => {
    try {
      setShowSpinner(true);
      const vehiclesWithPictures = await apiMainPage.GetFilteredAndSortedVehicles(phrase, minPrice, maxPrice, sort);
      setOffers(vehiclesWithPictures);
      setShowAll(false);
      scrollToTop();
      setShowSpinner(false);
    } catch (error) {
      setShowSpinner(false);
      console.error("Error searching for offers:", error);
    }
  };

  const handleShow = (id: number) => {
    navigate(`/carDetails/${id}`);
  };

  const handleShowMore = () => {
    setShowAll(true);
  };


  const scrollToTop = () => {
    if (topRef.current)
      topRef.current.scrollIntoView({ behavior: 'auto', block: 'start' });
  };

  return (
    <div>
      <div className="side-panel">
        <input
          type="text"
          placeholder="Enter phrase"
          value={phrase}
          onChange={(e) => setPhrase(e.target.value)}
          className="sidePanelSearch"
        />

        <div className="sortLabelFrame">
          <h1 className="sideMainHeader1">Sort </h1>
          <input
            type="radio"
            id="radio0"
            value="0"
            className="customCheckbox"
            name="sort"
            checked={sort === "none"}
            onChange={() => setSort("none")}
          />
          <label htmlFor="radio0" className="customSortLabel">
            None
          </label>
          <br />
          <input
            type="radio"
            id="radio1"
            value="1"
            className="customCheckbox"
            name="sort"
            checked={sort === "marka"}
            onChange={() => setSort("marka")}
          />
          <label htmlFor="radio1" className="customSortLabel">
            Brand
          </label>
          <br />
          <input
            type="radio"
            id="radio2"
            value="2"
            className="customCheckbox"
            name="sort"
            checked={sort === "cenadesc"}
            onChange={() => setSort("cenadesc")}
          />
          <label htmlFor="radio2" className="customSortLabel">
            Most expensive
          </label>
          <br />
          <input
            type="radio"
            id="radio3"
            value="3"
            className="customCheckbox"
            name="sort"
            checked={sort === "cenaasc"}
            onChange={() => setSort("cenaasc")}
          />
          <label htmlFor="radio3" className="customSortLabel">
            Least expensive
          </label>
          <br />
        </div>

        <div className="filterLabelFrame">
          <h1 className="sideMainHeader">Filter</h1>
          <h2 className="sideh1">By price</h2>
          <br />
          <label htmlFor="minPrice" className="customNumberLabel">
            Min
          </label>
          <br />
          <input
            type="number"
            id="minPrice"
            className="customNumber"
            value={minPrice}
            onChange={(e) => {
              const value = parseInt(e.target.value);
              if (isNaN(value)) {
                setMinPrice("");
              } else {
                setMinPrice(value);
              }
            }}
            onBlur={(e) => {
              const value = parseInt(e.target.value);
              if (isNaN(value)) {
                setMinPrice(0);
              } else {
                setMinPrice(value);
              }
            }}
            step="1000"
            min="0"
          />
          <br />
          <label htmlFor="maxPrice" className="customNumberLabel">
            Max
          </label>
          <br />
          <input
            type="number"
            id="maxIPrice"
            className="customNumber"
            value={maxPrice}
            onChange={(e) => {
              const value = parseInt(e.target.value);
              if (isNaN(value))
                setMaxPrice("");
              else
                setMaxPrice(value);
            }}
            onBlur={(e) => {
              const value = parseInt(e.target.value);
              if (isNaN(value)) {
                setMaxPrice(0);
              } else {
                setMaxPrice(value);
              }
            }}
            step="1000"
            min="0"
          />
          <br />
        </div>
        <div className="type">
          <h1>
            <button
              className="filterButton"
              onClick={() => filterAndSortOffers(phrase, minPrice, maxPrice, sort)}
            >
              Search and filter
            </button>
            <br />
          </h1>
        </div>
      </div>
      <div className="mainDiv">
        <div className="containersContainer" id="containersContainerID">
          {showSpinner && <div className="spinner-wrapper"><div className="spinner"></div></div>}
            {offers.slice(0, showAll ? offers.length : 10).map((offer, index) => (
              <div key={index} className="offerCard">
                <div className="offerDetails">
                  <h1>{offer.vehicle.brand} {offer.vehicle.model}</h1>
                  {offer.picture && 
                    <div className="imageAndOthers">
                      <img className="offerImage" src={`data:image/png;base64,${offer.picture}`} alt={`Offer ${offer.vehicle.brand} ${offer.vehicle.model}`} />
                      <div className="description">Price: ${offer.vehicle.price} 
                        <div className="buttonContainer">
                          <button className="offerButton" onClick={() => handleShow(offer.vehicle.vehicle_id)}>
                            Show
                          </button>
                        </div>
                      </div>
                    </div>
                  }
                </div>
              </div>
            ))}
            {!showAll && offers.length > 10 && (
              <button className="moreOffers" onClick={handleShowMore}>
                Show more
              </button>
            )}
        </div>
      </div>
      <div ref={topRef}></div>
    </div>
  );
}

export default App;