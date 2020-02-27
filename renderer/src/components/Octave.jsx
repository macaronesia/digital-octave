import React from 'react';
const {Pitch} = require('bindings')('simple-pitch');

const FREQ_A4 = 440;

export default class extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
      activeKeyIndex: null
    };
    this.pitch = new Pitch();
    this.ready = this.pitch.open();
  }

  pressDown(e, i) {
    let freq = FREQ_A4 * Math.pow(2, (i - 9) / 12);
    e.stopPropagation();
    this.setState({activeKeyIndex: i});
    this.pitch.start(freq);
  };

  pressUp(e) {
    e.stopPropagation();
    this.setState({activeKeyIndex: null});
    this.pitch.stop();
  };

  componentWillUnmount() {
    this.pitch.close();
  }

  render() {
    return (
      <div>
        {this.ready ? (
          <ul>
            {[0, 2, 4, 5, 7, 9, 11].map(i =>
              [0, 2, 5, 7, 9].includes(i) ? (
                <li
                  className={`key ${i === this.state.activeKeyIndex ? 'active' : ''}`}
                  onMouseDown={(e) => this.pressDown(e, i)}
                  onMouseUp={(e) => this.pressUp(e)}
                >
                  <div
                    className={`black-key ${i+1 === this.state.activeKeyIndex ? 'active' : ''}`}
                    onMouseDown={(e) => this.pressDown(e, i+1)}
                    onMouseUp={(e) => this.pressUp(e)}
                  ></div>
                </li>
              ) : (
                <li
                  className={`key ${i === this.state.activeKeyIndex ? 'active' : ''}`}
                  onMouseDown={(e) => this.pressDown(e, i)}
                  onMouseUp={(e) => this.pressUp(e)}
                ></li>
              )
            )}
          </ul>
        ) : (
          <p>Output device open failed.</p>
        )}
      </div>
    );
  }
};
